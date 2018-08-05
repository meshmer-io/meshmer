#include "include/tpool.h"
#include "../../include/meshmer/test/base.h"
#include "../../include/meshmer/test/test.h"
#include "../../include/meshmer/thread/thread.h"
#include "../../include/meshmer/atomic/cas.h"

MM_TEST_BASE_BEGIN

MM_STATIC_FUNCTION(mm_size_t, _mmi_tpool_reduce_worker_count, (MM_IN mm_tpool_t h_tpool)) {
  mm_size_t n_new_worker_count;
  mm_size_t n_old_worker_count = h_tpool->n_worker_count;

  do {
    MM_ASSERT(n_old_worker_count);

    n_new_worker_count = n_old_worker_count - 1;
  } while(MM_TEST(!mm_atomic_cas_64(&h_tpool->n_worker_count, &n_old_worker_count, &n_new_worker_count)));

  return n_new_worker_count;
}

MM_STATIC_FUNCTION(void, _mmi_tpool_stop, (MM_IN mm_tpool_t h_tpool)) {
  MM_ASSERT(h_tpool);

  h_tpool->b_running = mm_false;
  mm_event_signal(h_tpool->h_job_event);
}

MM_STATIC_FUNCTION(void, _mmi_tpool_worker, (MM_IN mm_tpool_t h_tpool)) {
  p_mmi_tpool_job_t p_job;
  
  while (MM_TEST(h_tpool->b_running)) {
    p_job = (p_mmi_tpool_job_t)mm_lf_queue_dequeue(h_tpool->h_pending_job_queue);

    if (MM_TEST(p_job)) {
      p_job->p_callback(h_tpool, p_job->p_context);

      if (MM_TEST(p_job->p_uninitialize))
        p_job->p_uninitialize(h_tpool, p_job->p_context);

      mm_mpool_return(h_tpool->h_free_jobs, p_job);
    } else
      mm_event_wait(h_tpool->h_job_event);
  }

  _mmi_tpool_stop(h_tpool);

  if (MM_TEST(!_mmi_tpool_reduce_worker_count(h_tpool)))
    mm_event_signal(h_tpool->h_shutdown_event);
}

MM_FUNCTION(mm_tpool_t, mm_tpool_create, (MM_IN mm_mm_t   h_mm,
                                          MM_IN mm_size_t n_worker_count)) {
  mm_tpool_t h_tpool;
  
  MM_ASSERT(h_mm);
  MM_ASSERT(n_worker_count);

  h_tpool = (mm_tpool_t)MM_MM_ALLOCATE(h_mm, sizeof (_mm_tpool_t));

  if (MM_TEST(h_tpool)) {
    h_tpool->h_job_event = mm_event_create(h_mm);

    if (MM_TEST(h_tpool->h_job_event)) {
      h_tpool->h_shutdown_event = mm_event_create(h_mm);

      if (MM_TEST(h_tpool->h_shutdown_event)) {
        h_tpool->h_free_jobs = mm_mpool_create(h_mm, sizeof (_mmi_tpool_job_t));

        if (MM_TEST(h_tpool->h_free_jobs)) {
          h_tpool->h_pending_job_queue = mm_lf_queue_create(h_mm);

          if (MM_TEST(h_tpool->h_pending_job_queue)) {
            mm_size_t n_i;
            
            h_tpool->n_worker_count = n_worker_count;
            h_tpool->b_running      = mm_true;
            h_tpool->h_mm           = h_mm;

            for (n_i = 0; n_i < n_worker_count; ++n_i)
              mm_thread_submit(h_mm, h_tpool, (mm_thread_callback_t)_mmi_tpool_worker);

            return h_tpool;
          }

          mm_mpool_destroy(h_tpool->h_free_jobs);
        }

        mm_event_destroy(h_tpool->h_shutdown_event);
      }

      mm_event_destroy(h_tpool->h_job_event);
    }

    MM_MM_FREE(h_mm, h_tpool, sizeof (_mm_tpool_t));
  }

  return NULL;
}

MM_FUNCTION(void, mm_tpool_destroy, (MM_IN mm_tpool_t h_tpool)) {
  p_mmi_tpool_job_t p_job;
  
  MM_ASSERT(h_tpool);

  _mmi_tpool_stop(h_tpool);
  mm_event_wait(h_tpool->h_shutdown_event);

  while (MM_TEST(p_job = (p_mmi_tpool_job_t)mm_lf_queue_dequeue(h_tpool->h_pending_job_queue))) {
    if (MM_TEST(p_job->p_uninitialize))
      p_job->p_uninitialize(h_tpool, p_job->p_context);

    mm_mpool_return(h_tpool->h_free_jobs, p_job);
  }
  
  mm_lf_queue_destroy(h_tpool->h_pending_job_queue);
  mm_mpool_destroy(h_tpool->h_free_jobs);
  mm_event_destroy(h_tpool->h_shutdown_event);
  mm_event_destroy(h_tpool->h_job_event);
  
  MM_MM_FREE(h_tpool->h_mm, h_tpool, sizeof (_mm_tpool_t));
}

MM_FUNCTION(void, mm_tpool_submit_job, (MM_IN     mm_tpool_t              h_tpool,
                                        MM_IN_OPT mm_pvoid_t              p_context,
                                        MM_IN     mm_tpool_job_callback_t p_callback,
                                        MM_IN_OPT mm_tpool_job_callback_t p_uninitialize)) {
  p_mmi_tpool_job_t p_job;
  
  MM_ASSERT(h_tpool);
  MM_ASSERT(p_callback);

  p_job = (p_mmi_tpool_job_t)mm_mpool_borrow(h_tpool->h_free_jobs);

  MM_ASSERT(p_job);

  p_job->p_context      = p_context;
  p_job->p_callback     = p_callback;
  p_job->p_uninitialize = p_uninitialize;

  mm_lf_queue_enqueue(h_tpool->h_pending_job_queue, p_job);
  mm_event_signal(h_tpool->h_job_event);
}

MM_TEST_BASE_END
