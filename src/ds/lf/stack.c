#include "include/stack.h"
#include "../../../include/meshmer/test/base.h"
#include "../../../include/meshmer/test/test.h"
#include "../../../include/meshmer/atomic/cas.h"

MM_TEST_BASE_BEGIN

MM_STATIC_FUNCTION(void, _mmi_lf_stack_push, (MM_IN p_mmi_lf_stack_head_t p_head,
                                              MM_IN p_mmi_lf_stack_node_t p_node)) {
  _mmi_lf_stack_head_t s_old_head = {p_head->p_head, p_head->n_version};
  _mmi_lf_stack_head_t s_new_head;

  do {
    p_node->p_next       = s_old_head.p_head;
    s_new_head.p_head    = p_node;
    s_new_head.n_version = s_old_head.n_version + 1;
  } while (MM_TEST(!mm_atomic_dcas(p_head, &s_old_head, &s_new_head)));
}

MM_STATIC_FUNCTION(p_mmi_lf_stack_node_t, _mmi_lf_stack_pop, (MM_IN p_mmi_lf_stack_head_t p_head)) {
  _mmi_lf_stack_head_t s_old_head = {p_head->p_head, p_head->n_version};
  _mmi_lf_stack_head_t s_new_head;

  while (MM_TEST(s_old_head.p_head)) {
    s_new_head.p_head    = s_old_head.p_head->p_next;
    s_new_head.n_version = s_old_head.n_version + 1;

    if (MM_TEST(mm_atomic_dcas(p_head, &s_old_head, &s_new_head)))
      return s_old_head.p_head;
  }

  return NULL;
}

MM_FUNCTION(mm_lf_stack_t, mm_lf_stack_create, (MM_IN mm_mm_t h_mm)) {
  mm_lf_stack_t h_stack;
  
  MM_ASSERT(h_mm);

  h_stack = (mm_lf_stack_t)MM_MM_ALLOCATE(h_mm, sizeof (_mm_lf_stack_t));

  if (MM_TEST(h_stack)) {
    h_stack->h_mm = h_mm;

    return h_stack;
  }

  return NULL;
}

MM_FUNCTION(void, mm_lf_stack_destroy, (MM_IN mm_lf_stack_t h_stack)) {
  mm_mm_t               h_mm;
  p_mmi_lf_stack_node_t p_node;
  
  MM_ASSERT(h_stack);
  MM_ASSERT(!h_stack->s_head.p_head);

  h_mm = h_stack->h_mm;

  while (MM_TEST(p_node = _mmi_lf_stack_pop(&h_stack->s_free_head)))
    MM_MM_FREE(h_mm, p_node, sizeof (_mmi_lf_stack_node_t));

  MM_MM_FREE(h_mm, h_stack, sizeof (_mm_lf_stack_t));
}

MM_FUNCTION(void, mm_lf_stack_push, (MM_IN mm_lf_stack_t h_stack,
                                     MM_IN mm_pvoid_t    p_value)) {
  p_mmi_lf_stack_node_t p_node;
  
  MM_ASSERT(h_stack);
  MM_ASSERT(p_value);

  p_node = _mmi_lf_stack_pop(&h_stack->s_free_head);

  if (MM_TEST(!p_node))
    p_node = (p_mmi_lf_stack_node_t)MM_MM_ALLOCATE(h_stack->h_mm, sizeof (_mmi_lf_stack_node_t));

  MM_ASSERT(p_node);

  p_node->p_value = p_value;

  _mmi_lf_stack_push(&h_stack->s_head, p_node);
}

MM_FUNCTION(mm_pvoid_t, mm_lf_stack_pop, (MM_IN mm_lf_stack_t h_stack)) {
  p_mmi_lf_stack_node_t p_node;
  
  MM_ASSERT(h_stack);

  p_node = _mmi_lf_stack_pop(&h_stack->s_head);

  if (MM_TEST(p_node)) {
    mm_pvoid_t p_value = p_node->p_value;

    _mmi_lf_stack_push(&h_stack->s_free_head, p_node);

    return p_value;
  }

  return NULL;
}

MM_TEST_BASE_END
