#include "include/event.h"
#include "../../../../include/meshmer/test/base.h"
#include "../../../../include/meshmer/test/test.h"

MM_TEST_BASE_BEGIN

MM_FUNCTION(mm_event_t, mm_event_create, (MM_IN mm_mm_t h_mm)) {
  mm_event_t h_event;
  
  MM_TEST(h_mm);

  h_event = (mm_event_t)MM_MM_ALLOCATE(h_mm, sizeof (_mm_event_t));

  if (MM_TEST(h_event)) {
    h_event->h_event = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (MM_TEST(h_event->h_event)) {
      h_event->h_mm = h_mm;

      return h_event;
    }

    MM_MM_FREE(h_mm, h_event, sizeof (_mm_event_t));
  }

  return NULL;
}

MM_FUNCTION(void, mm_event_destroy, (MM_IN mm_event_t h_event)) {
  MM_ASSERT(h_event);

  MM_ASSERT(CloseHandle(h_event->h_event));

  MM_MM_FREE(h_event->h_mm, h_event, sizeof (_mm_event_t));
}

MM_FUNCTION(void, mm_event_signal, (MM_IN mm_event_t h_event)) {
  MM_ASSERT(h_event);
  MM_ASSERT(SetEvent(h_event->h_event));
}

MM_FUNCTION(void, mm_event_wait, (MM_IN mm_event_t h_event)) {
  MM_ASSERT(h_event);
  MM_ASSERT(WAIT_OBJECT_0 == WaitForSingleObject(h_event->h_event, INFINITE));
}

MM_TEST_BASE_END
