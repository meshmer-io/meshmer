#if !defined(__256904D8B6273877AA35A6EA07F__)
# define __256904D8B6273877AA35A6EA07F__

# include "../../../include/meshmer/mm/mpool.h"
# include "../../../include/meshmer/ds/lf/stack.h"

MM_DEFINE_HANDLE(mm_mpool_t, {
    mm_lf_stack_t h_free_elements;
    mm_mm_t       h_mm;
    mm_size_t     n_element_size;
  });

#endif /* !__256904D8B6273877AA35A6EA07F__ */
