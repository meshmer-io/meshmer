#include "include/queue.h"
#include "../../../include/meshmer/test/base.h"
#include "../../../include/meshmer/test/test.h"
#include "../../../include/meshmer/atomic/cas.h"

# define MMI_LF_QUEUE_COPY_POINTER(__source__, __destination__)  \
  (__destination__).p_node    = (__source__).p_node;             \
  (__destination__).n_version = (__source__).n_version

# define MMI_LF_QUEUE_COMPARE_POINTERS(__left__, __right__)             \
  (((__left__).p_node == (__right__).p_node) &&                        \
   ((__right__).n_version == (__right__).n_version))

MM_TEST_BASE_BEGIN

MM_STATIC_FUNCTION(void, _mmi_lf_queue_head_enqueue, (MM_IN p_mmi_lf_queue_head_t p_head,
                                                      MM_IN p_mmi_lf_queue_node_t p_node)) {
  _mmi_lf_queue_pointer_t s_tail;
  _mmi_lf_queue_pointer_t s_next;
  _mmi_lf_queue_pointer_t s_node;

  MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);
  MMI_LF_QUEUE_COPY_POINTER(s_tail.p_node->s_next, s_next);

  p_node->s_next.p_node    = NULL;
  p_node->s_next.n_version = 1;

  for (;;) {

    if (MM_TEST(MMI_LF_QUEUE_COMPARE_POINTERS(s_tail, p_head->s_tail))) {
      if (MM_TEST(s_next.p_node)) {
        s_node.p_node    = s_next.p_node;
        s_node.n_version = s_tail.n_version + 1;
        
        (void)mm_atomic_dcas(&p_head->s_tail, &s_tail, &s_node);
        
        MMI_LF_QUEUE_COPY_POINTER(s_tail.p_node->s_next, s_next);

        continue;
      } else {
        s_node.p_node    = p_node;
        s_node.n_version = s_next.n_version + 1;

        if (MM_TEST(mm_atomic_dcas(&s_tail.p_node->s_next, &s_next, &s_node)))
          break;

        MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);

        continue;
      }
    }
    
    MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);
    MMI_LF_QUEUE_COPY_POINTER(s_tail.p_node->s_next, s_next);
  }

  s_node.p_node    = p_node;
  s_node.n_version = s_tail.n_version + 1;
  
  (void)mm_atomic_dcas(&p_head->s_tail, &s_tail, &s_node);
}

MM_STATIC_FUNCTION(p_mmi_lf_queue_node_t, _mmi_lf_queue_head_dequeue, (MM_IN p_mmi_lf_queue_head_t p_head)) {
  _mmi_lf_queue_pointer_t s_head;
  _mmi_lf_queue_pointer_t s_tail;
  _mmi_lf_queue_pointer_t s_next;
  _mmi_lf_queue_pointer_t s_node;

  MMI_LF_QUEUE_COPY_POINTER(p_head->s_head, s_head);
  MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);

  for (;;) {
    MMI_LF_QUEUE_COPY_POINTER(s_head.p_node->s_next, s_next);

    if (MM_TEST(MMI_LF_QUEUE_COMPARE_POINTERS(s_head, p_head->s_head))) {
      s_node.p_node = s_next.p_node;
      
      if (MM_TEST(s_head.p_node == s_tail.p_node)) {
        if (MM_TEST(!s_next.p_node))
          return NULL;

        s_node.n_version = s_tail.n_version + 1;

        (void)mm_atomic_dcas(&p_head->s_tail, &s_tail, &s_node);

        MMI_LF_QUEUE_COPY_POINTER(p_head->s_head, s_head);
        
        continue;
      } else {
        s_node.n_version = s_head.n_version + 1;

        if (MM_TEST(mm_atomic_dcas(&p_head->s_head, &s_head, &s_node)))
          return s_next.p_node;

        MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);

        continue;
      }
    }

    MMI_LF_QUEUE_COPY_POINTER(p_head->s_head, s_head);
    MMI_LF_QUEUE_COPY_POINTER(p_head->s_tail, s_tail);
  }
}

MM_STATIC_FUNCTION(p_mmi_lf_queue_node_t, _mmi_lf_queue_borrow_node, (MM_IN mm_lf_queue_t h_queue)) {
  p_mmi_lf_queue_node_t p_node = _mmi_lf_queue_head_dequeue(&h_queue->s_free_head);

  if (MM_TEST(!p_node))
    p_node = (p_mmi_lf_queue_node_t)MM_MM_ALLOCATE(h_queue->h_mm, sizeof (_mmi_lf_queue_node_t));

  MM_ASSERT(p_node);

  return p_node;
}

MM_STATIC_FUNCTION(mm_bool_t, _mmi_lf_queue_head_initialize, (MM_IN mm_lf_queue_t         h_queue,
                                                              MM_IN p_mmi_lf_queue_head_t p_head)) {
  p_mmi_lf_queue_node_t p_node = _mmi_lf_queue_borrow_node(h_queue);

  if (MM_TEST(p_node)) {
    p_head->s_head.p_node   =
      p_head->s_tail.p_node = p_node;
    p_head->s_head.n_version   =
      p_head->s_tail.n_version = 1;

    return mm_true;
  }

  return mm_false;
}

MM_FUNCTION(mm_lf_queue_t, mm_lf_queue_create, (MM_IN mm_mm_t h_mm)) {
  mm_lf_queue_t h_queue;
  
  MM_ASSERT(h_mm);

  h_queue = (mm_lf_queue_t)MM_MM_ALLOCATE(h_mm, sizeof (_mm_lf_queue_t));

  if (MM_TEST(h_queue)) {
    if (MM_TEST(_mmi_lf_queue_head_initialize(h_queue, &h_queue->s_head)) &&
        MM_TEST(_mmi_lf_queue_head_initialize(h_queue, &h_queue->s_free_head))) {
      h_queue->h_mm = h_mm;

      return h_queue;
    }
  }

  return NULL;
}

MM_FUNCTION(void, mm_lf_queue_destroy, (MM_IN mm_lf_queue_t h_queue)) {
  p_mmi_lf_queue_node_t p_node;
  p_mmi_lf_queue_head_t p_free_head;
  mm_mm_t               h_mm;
  
  MM_ASSERT(h_queue);
  MM_ASSERT(!h_queue->s_head.s_head.p_node);
  MM_ASSERT(!h_queue->s_head.s_tail.p_node);

  p_free_head = &h_queue->s_free_head;
  h_mm        = h_queue->h_mm;

  while (MM_TEST(p_node = _mmi_lf_queue_head_dequeue(p_free_head)))
    MM_MM_FREE(h_mm, p_node, sizeof (_mmi_lf_queue_node_t));

  MM_MM_FREE(h_mm, h_queue, sizeof (_mm_lf_queue_t));
}

MM_FUNCTION(void, mm_lf_queue_enqueue, (MM_IN mm_lf_queue_t h_queue,
                                        MM_IN mm_pvoid_t    p_value)) {
  p_mmi_lf_queue_node_t p_node;
  
  MM_ASSERT(h_queue);
  MM_ASSERT(p_value);

  p_node = _mmi_lf_queue_borrow_node(h_queue);

  MM_ASSERT(p_node);

  p_node->p_value = p_value;

  _mmi_lf_queue_head_enqueue(&h_queue->s_head, p_node);
}

MM_FUNCTION(mm_pvoid_t, mm_lf_queue_dequeue, (MM_IN mm_lf_queue_t h_queue)) {
  p_mmi_lf_queue_node_t p_node;
  
  MM_ASSERT(h_queue);

  p_node = _mmi_lf_queue_head_dequeue(&h_queue->s_head);

  if (MM_TEST(p_node)) {
    mm_pvoid_t p_value = p_node->p_value;

    _mmi_lf_queue_head_enqueue(&h_queue->s_free_head, p_node);

    return p_value;
  }

  return NULL;
}

MM_TEST_BASE_END
