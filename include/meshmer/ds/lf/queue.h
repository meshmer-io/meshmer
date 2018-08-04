#if !defined(__014CD1B63C67699BFBB184746D3__)
# define __014CD1B63C67699BFBB184746D3__

# include "../../common/macros.h"
# include "../../common/types.h"
# include "../../mm/mm.h"

MM_DECLARE_HANDLE(mm_lf_queue_t);

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_lf_queue_t, mm_lf_queue_create, (MM_IN mm_mm_t h_mm));
  MM_FUNCTION(void, mm_lf_queue_destroy, (MM_IN mm_lf_queue_t h_queue));

  MM_FUNCTION(void, mm_lf_queue_enqueue, (MM_IN mm_lf_queue_t h_queue,
                                          MM_IN mm_pvoid_t    p_value));
  MM_FUNCTION(mm_pvoid_t, mm_lf_queue_dequeue, (MM_IN mm_lf_queue_t h_queue));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__014CD1B63C67699BFBB184746D3__ */
