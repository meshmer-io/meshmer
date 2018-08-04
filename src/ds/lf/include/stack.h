#if !defined(__BDE4C82D325663451946FCC77CC__)
# define __BDE4C82D325663451946FCC77CC__

# include "../../../../include/meshmer/ds/lf/stack.h"

MM_DEFINE_STRUCT(_mmi_lf_stack_node_t, {
    p_mmi_lf_stack_node_t p_next;
    mm_pvoid_t            p_value;
  });
MM_DEFINE_DOUBLE_ALIGNED_STRUCT(_mmi_lf_stack_head_t, {
    p_mmi_lf_stack_node_t p_head;
    mm_word_t             n_version;
  });
MM_DEFINE_HANDLE(mm_lf_stack_t, {
    _mmi_lf_stack_head_t s_head;
    _mmi_lf_stack_head_t s_free_head;
    mm_mm_t              h_mm;
  });

#endif /* !__BDE4C82D325663451946FCC77CC__ */
