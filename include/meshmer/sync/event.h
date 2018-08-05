#if !defined(__32E832115319F70565D6C5AB97B__)
# define __32E832115319F70565D6C5AB97B__

# include "../mm/mm.h"

MM_DECLARE_HANDLE(mm_event_t);

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_event_t, mm_event_create, (MM_IN mm_mm_t h_mm));
  MM_FUNCTION(void, mm_event_destroy, (MM_IN mm_event_t h_event));

  MM_FUNCTION(void, mm_event_signal, (MM_IN mm_event_t h_event));
  MM_FUNCTION(void, mm_event_wait, (MM_IN mm_event_t h_event));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__32E832115319F70565D6C5AB97B__ */
