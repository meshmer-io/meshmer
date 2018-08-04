#if !defined(__30FF390F1121115C14B8F517898__)
# define __30FF390F1121115C14B8F517898__

# include "../../../include/meshmer/mm/mm.h"

MM_DEFINE_HANDLE(mm_mm_t, {
    mm_mm_t             h_parent;
    mm_size_t           n_quota;
    mm_aligned_uint64_t n_reserved;
  });

MM_INTERNAL_FUNCTION(mm_mm_t, _mmi_mm_create, (MM_IN mm_size_t n_quota));

MM_INTERNAL_FUNCTION(mm_bool_t, _mmi_mm_reserve_quota, (MM_IN mm_mm_t   h_mm,
                                                        MM_IN mm_size_t n_size));
MM_INTERNAL_FUNCTION(void, _mmi_mm_release_quota, (MM_IN mm_mm_t   h_mm,
                                                   MM_IN mm_size_t n_size));

#endif /* !__30FF390F1121115C14B8F517898__ */
