#if !defined(__D5CF6FCD8083B3514A7F722F3BD__)
# define __D5CF6FCD8083B3514A7F722F3BD__

# include "../../../include/meshmer/atomic/cas.h"

MM_INTERNAL_FUNCTION(mm_bool_t, _mmi_atomic_cas_64, (MM_INOUT pmm_aligned_uint64_t  p_buffer,
                                                     MM_INOUT pmm_volatile_uint64_t p_old_value,
                                                     MM_IN    pmm_uint64_t          p_new_value));
MM_INTERNAL_FUNCTION(mm_bool_t, _mmi_atomic_dcas, (MM_INOUT mm_volatile_pvoid_t p_buffer,
                                                   MM_INOUT mm_volatile_pvoid_t p_old_value,
                                                   MM_IN    mm_pvoid_t          p_new_value));

#endif /* !__D5CF6FCD8083B3514A7F722F3BD__ */
