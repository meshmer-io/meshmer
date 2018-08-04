#if !defined(__409B82036C6E3C0DFB26B7DED45__)
# define __409B82036C6E3C0DFB26B7DED45__

# include "../common/macros.h"
# include "../common/types.h"

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_bool_t, mm_atomic_cas_64, (MM_INOUT pmm_aligned_uint64_t  p_buffer,
                                            MM_INOUT pmm_volatile_uint64_t p_old_value,
                                            MM_IN    pmm_uint64_t          p_new_value));
  MM_FUNCTION(mm_bool_t, mm_atomic_dcas, (MM_INOUT mm_volatile_pvoid_t p_buffer,
                                          MM_INOUT mm_volatile_pvoid_t p_old_value,
                                          MM_IN    mm_pvoid_t          p_new_value));
  
# if defined(__cplusplus)
}
# endif

#endif /* !__409B82036C6E3C0DFB26B7DED45__ */
