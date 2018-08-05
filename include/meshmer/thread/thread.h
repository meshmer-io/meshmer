#if !defined(__DC8BE38428DF31E85E285A3334B__)
# define __DC8BE38428DF31E85E285A3334B__

# include "../mm/mm.h"

MM_CALLBACK(void, mm_thread_callback_t, (MM_IN mm_pvoid_t p_context));

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(void, mm_thread_submit, (MM_IN     mm_mm_t              h_mm,
                                       MM_IN_OPT mm_pvoid_t           p_context,
                                       MM_IN     mm_thread_callback_t p_callback));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__DC8BE38428DF31E85E285A3334B__ */
