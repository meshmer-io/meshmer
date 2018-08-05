#if !defined(__07E5437EE4914573FC643524418__)
# define __07E5437EE4914573FC643524418__

# include "../mm/mm.h"

MM_DECLARE_HANDLE(mm_tpool_t);

MM_CALLBACK(void, mm_tpool_job_callback_t, (MM_IN     mm_tpool_t h_tpool,
                                            MM_IN_OPT mm_pvoid_t p_context));

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_tpool_t, mm_tpool_create, (MM_IN mm_mm_t   h_mm,
                                            MM_IN mm_size_t n_worker_count));
  MM_FUNCTION(void, mm_tpool_destroy, (MM_IN mm_tpool_t h_tpool));

  MM_FUNCTION(void, mm_tpool_submit_job, (MM_IN     mm_tpool_t              h_tpool,
                                          MM_IN_OPT mm_pvoid_t              p_context,
                                          MM_IN     mm_tpool_job_callback_t p_callback,
                                          MM_IN_OPT mm_tpool_job_callback_t p_uninitialize));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__07E5437EE4914573FC643524418__ */
