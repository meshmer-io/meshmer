#if !defined(__21F8964A4CB2852911FCC25FBD2__)
# define __21F8964A4CB2852911FCC25FBD2__

# include "../../../../../include/meshmer/thread/thread.h"

MM_DEFINE_STRUCT(_mmi_msvc_user_thread_t, {
    mm_mm_t              h_mm;
    mm_pvoid_t           p_context;
    mm_thread_callback_t p_callback;
  });

#endif /* !__21F8964A4CB2852911FCC25FBD2__ */
