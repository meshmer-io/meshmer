#include "include/mpool.h"
#include "../../include/meshmer/test/base.h"
#include "../../include/meshmer/test/test.h"

MM_TEST_BASE_BEGIN

MM_FUNCTION(mm_mpool_t, mm_mpool_create, (MM_IN mm_mm_t   h_mm,
                                          MM_IN mm_size_t n_element_size)) {
  mm_mpool_t h_mpool;
  
  MM_ASSERT(h_mm);
  MM_ASSERT(n_element_size);

  h_mpool = (mm_mpool_t)MM_MM_ALLOCATE(h_mm, sizeof (_mm_mpool_t));

  if (MM_TEST(h_mpool)) {
    h_mpool->h_free_elements = mm_lf_stack_create(h_mm);

    if (MM_TEST(h_mpool->h_free_elements)) {
      h_mpool->h_mm           = h_mm;
      h_mpool->n_element_size = n_element_size;

      return h_mpool;
    }

    MM_MM_FREE(h_mm, h_mpool, sizeof (_mm_mpool_t));
  }

  return NULL;
}

MM_FUNCTION(void, mm_mpool_destroy, (MM_IN mm_mpool_t h_mpool)) {
  mm_mm_t       h_mm;
  mm_lf_stack_t h_free_elements;
  mm_pvoid_t    p_element;
  mm_size_t     n_element_size;
  
  MM_ASSERT(h_mpool);

  h_mm            = h_mpool->h_mm;
  h_free_elements = h_mpool->h_free_elements;
  n_element_size  = h_mpool->n_element_size;

  while (MM_TEST(p_element = mm_lf_stack_pop(h_free_elements)))
    MM_MM_FREE(h_mm, p_element, n_element_size);

  mm_lf_stack_destroy(h_free_elements);
  MM_MM_FREE(h_mm, h_mpool, sizeof (_mm_mpool_t));
}

MM_FUNCTION(mm_pvoid_t, mm_mpool_borrow, (MM_IN mm_mpool_t h_mpool)) {
  mm_pvoid_t p_element;
  
  MM_ASSERT(h_mpool);

  p_element = mm_lf_stack_pop(h_mpool->h_free_elements);

  if (MM_TEST(p_element))
    return p_element;

  return MM_MM_ALLOCATE(h_mpool->h_mm, h_mpool->n_element_size);
}

MM_FUNCTION(void, mm_mpool_return, (MM_IN mm_mpool_t h_mpool,
                                    MM_IN mm_pvoid_t p_element)) {
  MM_ASSERT(h_mpool);
  MM_ASSERT(p_element);

  mm_lf_stack_push(h_mpool->h_free_elements, p_element);
}

MM_FUNCTION(mm_pvoid_t, mm_mpool_borrow_trace, (MM_IN mm_mpool_t  h_mpool,
                                                MM_IN mm_string_t sz_file_name,
                                                MM_IN mm_uint32_t n_line_number)) {
  MM_ASSERT(sz_file_name);

  return mm_mpool_borrow(h_mpool);
}

MM_FUNCTION(void, mm_mpool_return_trace, (MM_IN mm_mpool_t  h_mpool,
                                          MM_IN mm_pvoid_t  p_element,
                                          MM_IN mm_string_t sz_file_name,
                                          MM_IN mm_uint32_t n_line_number)) {
  MM_ASSERT(sz_file_name);

  mm_mpool_return(h_mpool, p_element);
}

MM_TEST_BASE_END
