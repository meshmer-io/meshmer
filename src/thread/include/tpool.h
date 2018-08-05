#if !defined(__B9555440F6D69D4816A45BC37D9__)
# define __B9555440F6D69D4816A45BC37D9__

# include "../../../include/meshmer/thread/tpool.h"
# include "../../../include/meshmer/sync/event.h"
# include "../../../include/meshmer/mm/mpool.h"
# include "../../../include/meshmer/ds/lf/queue.h"

MM_DEFINE_STRUCT(_mmi_tpool_job_t, {
    mm_pvoid_t              p_context;
    mm_tpool_job_callback_t p_callback;
    mm_tpool_job_callback_t p_uninitialize;
  });

MM_DEFINE_HANDLE(mm_tpool_t, {
    mm_size_t     n_worker_count;
    mm_bool_t     b_running;
    mm_event_t    h_job_event;
    mm_event_t    h_shutdown_event;
    mm_mpool_t    h_free_jobs;
    mm_lf_queue_t h_pending_job_queue;
    mm_mm_t       h_mm;
  });

#endif /* !__B9555440F6D69D4816A45BC37D9__ */
