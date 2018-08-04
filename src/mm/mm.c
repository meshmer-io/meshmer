#include "include/mm.h"
#include "../../include/meshmer/test/base.h"
#include "../../include/meshmer/test/test.h"
#include "../../include/meshmer/atomic/cas.h"

MM_TEST_BASE_BEGIN

MM_INTERNAL_FUNCTION(mm_bool_t, _mmi_mm_reserve_quota, (MM_IN mm_mm_t   h_mm,
                                                        MM_IN mm_size_t n_size)) {
  volatile mm_size_t n_old_reserved;
  mm_size_t n_new_reserved;
  
  MM_ASSERT(h_mm);
  MM_ASSERT(n_size);

  n_old_reserved = h_mm->n_reserved;

  for (;;) {
    n_new_reserved = n_old_reserved + n_size;

    if (MM_TEST(n_new_reserved <= h_mm->n_quota)) {
      if (MM_TEST(mm_atomic_cas_64(&h_mm->n_reserved, &n_old_reserved, &n_new_reserved)))
        return mm_true;
    } else return mm_false;
  }
}

MM_INTERNAL_FUNCTION(void, _mmi_mm_release_quota, (MM_IN mm_mm_t   h_mm,
                                                   MM_IN mm_size_t n_size)) {
  volatile mm_size_t n_old_reserved;
  mm_size_t n_new_reserved;
  
  MM_ASSERT(h_mm);
  MM_ASSERT(n_size);

  n_old_reserved = h_mm->n_reserved;

  for (;;) {
    MM_ASSERT(n_old_reserved >= n_size);

    n_new_reserved = n_old_reserved - n_size;

    if (MM_TEST(mm_atomic_cas_64(&h_mm->n_reserved, &n_old_reserved, &n_new_reserved)))
      return;
  }
}

MM_TEST_BASE_END
