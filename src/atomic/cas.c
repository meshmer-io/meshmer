#include "include/cas.h"
#include "../../include/meshmer/test/base.h"
#include "../../include/meshmer/test/test.h"

MM_TEST_BASE_BEGIN

MM_FUNCTION(mm_bool_t, mm_atomic_cas_64, (MM_INOUT pmm_aligned_uint64_t  p_buffer,
                                          MM_INOUT pmm_volatile_uint64_t p_old_value,
                                          MM_IN    pmm_uint64_t          p_new_value)) {
  MM_ASSERT(p_buffer);
  MM_ASSERT(p_old_value);
  MM_ASSERT(p_new_value);

  return _mmi_atomic_cas_64(p_buffer, p_old_value, p_new_value);
}

MM_FUNCTION(mm_bool_t, mm_atomic_dcas, (MM_INOUT mm_volatile_pvoid_t p_buffer,
                                        MM_INOUT mm_volatile_pvoid_t p_old_value,
                                        MM_IN    mm_pvoid_t          p_new_value)) {
  MM_ASSERT(p_buffer);
  MM_ASSERT(p_old_value);
  MM_ASSERT(p_new_value);

  return _mmi_atomic_dcas(p_buffer, p_old_value, p_new_value);
}

MM_TEST_BASE_END
