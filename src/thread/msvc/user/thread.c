#include "include/thread.h"
#include "../../../../include/meshmer/test/base.h"
#include "../../../../include/meshmer/test/test.h"

MM_TEST_BASE_BEGIN

MM_STATIC_FUNCTION(DWORD, _mmi_thread, (MM_IN p_mmi_msvc_user_thread_t p_thread)) {
  mm_pvoid_t           p_context;
  mm_thread_callback_t p_callback;
  
  MM_ASSERT(p_thread);

  p_context  = p_thread->p_context;
  p_callback = p_thread->p_callback;

  MM_MM_FREE(p_thread->h_mm, p_thread, sizeof (_mmi_msvc_user_thread_t));

  p_callback(p_context);

  return GetLastError();
}

MM_FUNCTION(void, mm_thread_submit, (MM_IN     mm_mm_t              h_mm,
                                     MM_IN_OPT mm_pvoid_t           p_context,
                                     MM_IN     mm_thread_callback_t p_callback)) {
  HANDLE                   h_thread;
  DWORD                    n_thread_id;
  p_mmi_msvc_user_thread_t p_thread;

  MM_ASSERT(h_mm);
  MM_ASSERT(p_callback);

  p_thread = (p_mmi_msvc_user_thread_t)MM_MM_ALLOCATE(h_mm, sizeof (_mmi_msvc_user_thread_t));

  MM_ASSERT(p_thread);

  p_thread->h_mm       = h_mm;
  p_thread->p_context  = p_context;
  p_thread->p_callback = p_callback;

  h_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)_mmi_thread, p_thread, 0, &n_thread_id);

  MM_ASSERT(h_thread);
  MM_ASSERT(CloseHandle(h_thread));
}

MM_TEST_BASE_END
