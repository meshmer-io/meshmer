#include "include/mm.h"
#include "../../../../include/meshmer/test/base.h"
#include "../../../../include/meshmer/test/test.h"

MM_TEST_BASE_BEGIN

MM_STATIC_FUNCTION(mm_mm_t, _mmi_mm_initialize, (MM_IN p_mmi_mm_msvc_user_t p_mm,
                                                 MM_IN mm_mm_t              h_parent,
                                                 MM_IN mm_size_t            n_quota)) {
  HANDLE h_heap;
  
  MM_ASSERT(p_mm);
  MM_ASSERT(n_quota);

  h_heap = HeapCreate(0, 0, (SIZE_T)n_quota);

  if (MM_TEST(h_heap)) {
    mm_mm_t h_mm = (mm_mm_t)p_mm;

    h_mm->h_parent = h_parent;
    h_mm->n_quota  = n_quota;
    p_mm->h_heap   = h_heap;

    return h_mm;
  }

  return NULL;
}

MM_INTERNAL_FUNCTION(mm_mm_t, _mmi_mm_create, (MM_IN mm_size_t n_quota)) {
  HANDLE               h_heap = GetProcessHeap();
  p_mmi_mm_msvc_user_t p_mm;
  
  MM_ASSERT(n_quota);
  MM_ASSERT(h_heap);

  p_mm = (p_mmi_mm_msvc_user_t)HeapAlloc(h_heap, HEAP_ZERO_MEMORY, sizeof (_mmi_mm_msvc_user_t));

  if (MM_TEST(p_mm)) {
    mm_mm_t h_mm = _mmi_mm_initialize(p_mm, NULL, n_quota);

    if (MM_TEST(h_mm))
      return h_mm;

    MM_ASSERT(HeapFree(h_heap, 0, p_mm));
  }

  return NULL;
}

MM_FUNCTION(mm_mm_t, mm_mm_create, (MM_IN mm_mm_t   h_parent,
                                    MM_IN mm_size_t n_quota)) {
  MM_ASSERT(h_parent);
  MM_ASSERT(n_quota);

  if (MM_TEST(_mmi_mm_reserve_quota(h_parent, n_quota))) {
    p_mmi_mm_msvc_user_t p_mm = (p_mmi_mm_msvc_user_t)MM_MM_ALLOCATE(h_parent, sizeof (_mmi_mm_msvc_user_t));

    if (MM_TEST(p_mm)) {
      mm_mm_t h_mm = _mmi_mm_initialize(p_mm, h_parent, n_quota);

      if (MM_TEST(h_mm))
        return h_mm;

      MM_MM_FREE(h_parent, p_mm, sizeof (_mmi_mm_msvc_user_t));
    }

    _mmi_mm_release_quota(h_parent, n_quota);
  }

  return NULL;
}

MM_FUNCTION(void, mm_mm_destroy, (MM_IN mm_mm_t h_mm)) {
  mm_mm_t h_parent;
  
  MM_ASSERT(h_mm);
  MM_ASSERT(!h_mm->n_reserved);

  MM_ASSERT(HeapDestroy(((p_mmi_mm_msvc_user_t)h_mm)->h_heap));

  h_parent = h_mm->h_parent;
  
  if (MM_TEST(h_parent)) {
    mm_size_t n_quota = h_mm->n_quota;

    MM_MM_FREE(h_parent, h_mm, sizeof (_mmi_mm_msvc_user_t));
    _mmi_mm_release_quota(h_parent, n_quota);
  } else {
    HANDLE h_heap = GetProcessHeap();

    MM_ASSERT(HeapFree(h_heap, 0, h_mm));
  }
}

MM_FUNCTION(mm_pvoid_t, mm_mm_allocate, (MM_IN mm_mm_t   h_mm,
                                         MM_IN mm_size_t n_size)) {
  MM_ASSERT(h_mm);
  MM_ASSERT(n_size);

  if (MM_TEST(_mmi_mm_reserve_quota(h_mm, n_size))) {
    mm_pvoid_t p_buffer = (mm_pvoid_t)HeapAlloc(((p_mmi_mm_msvc_user_t)h_mm)->h_heap, HEAP_ZERO_MEMORY, (SIZE_T)n_size);

    if (MM_TEST(p_buffer))
      return p_buffer;

    _mmi_mm_release_quota(h_mm, n_size);
  }

  return NULL;
}

MM_FUNCTION(void, mm_mm_free, (MM_IN mm_mm_t    h_mm,
                               MM_IN mm_pvoid_t p_buffer,
                               MM_IN mm_size_t  n_size)) {
  MM_ASSERT(h_mm);
  MM_ASSERT(p_buffer);
  MM_ASSERT(n_size);

  MM_ASSERT(HeapFree(((p_mmi_mm_msvc_user_t)h_mm)->h_heap, 0, p_buffer));
  _mmi_mm_release_quota(h_mm, n_size);
}

MM_FUNCTION(mm_pvoid_t, mm_mm_allocate_trace, (MM_IN mm_mm_t     h_mm,
                                               MM_IN mm_size_t   n_size,
                                               MM_IN mm_string_t sz_file_name,
                                               MM_IN mm_uint32_t n_line_number)) {
  MM_ASSERT(sz_file_name);

  return mm_mm_allocate(h_mm, n_size);
}

MM_FUNCTION(void, mm_mm_free_trace, (MM_IN mm_mm_t     h_mm,
                                     MM_IN mm_pvoid_t  p_buffer,
                                     MM_IN mm_size_t   n_size,
                                     MM_IN mm_string_t sz_file_name,
                                     MM_IN mm_uint32_t n_line_number)) {
  MM_ASSERT(sz_file_name);

  mm_mm_free(h_mm, p_buffer, n_size);
}

MM_TEST_BASE_END
