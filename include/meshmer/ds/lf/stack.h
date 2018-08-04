#if !defined(__AFB347C69E40A77578DFB9DA92E__)
# define __AFB347C69E40A77578DFB9DA92E__

# include "../../common/macros.h"
# include "../../common/types.h"
# include "../../mm/mm.h"

MM_DECLARE_HANDLE(mm_lf_stack_t);

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_lf_stack_t, mm_lf_stack_create, (MM_IN mm_mm_t h_mm));
  MM_FUNCTION(void, mm_lf_stack_destroy, (MM_IN mm_lf_stack_t h_stack));

  MM_FUNCTION(void, mm_lf_stack_push, (MM_IN mm_lf_stack_t h_stack,
                                       MM_IN mm_pvoid_t    p_value));
  MM_FUNCTION(mm_pvoid_t, mm_lf_stack_pop, (MM_IN mm_lf_stack_t h_stack));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__AFB347C69E40A77578DFB9DA92E__ */
