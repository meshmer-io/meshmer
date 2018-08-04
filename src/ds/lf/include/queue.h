#if !defined(__EAD67917182EC7093838687CC12__)
# define __EAD67917182EC7093838687CC12__

# include "../../../../include/meshmer/ds/lf/queue.h"

MM_DECLARE_STRUCT(_mmi_lf_queue_pointer_t);
MM_DECLARE_STRUCT(_mmi_lf_queue_node_t);
MM_DECLARE_STRUCT(_mmi_lf_queue_head_t);

MM_DEFINE_DOUBLE_ALIGNED_STRUCT(_mmi_lf_queue_pointer_t, {
    p_mmi_lf_queue_node_t p_node;
    mm_word_t             n_version;
  });
MM_DEFINE_STRUCT(_mmi_lf_queue_node_t, {
    _mmi_lf_queue_pointer_t s_next;
    mm_pvoid_t              p_value;
  });
MM_DEFINE_STRUCT(_mmi_lf_queue_head_t, {
    _mmi_lf_queue_pointer_t s_head;
    _mmi_lf_queue_pointer_t s_tail;
  });
MM_DEFINE_HANDLE(mm_lf_queue_t, {
    _mmi_lf_queue_head_t s_head;
    _mmi_lf_queue_head_t s_free_head;
    mm_mm_t              h_mm;
  });

#endif /* !__EAD67917182EC7093838687CC12__ */
