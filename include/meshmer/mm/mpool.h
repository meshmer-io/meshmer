#if !defined(__B35687F9AD62F1CBD20BD6162C8__)
# define __B35687F9AD62F1CBD20BD6162C8__

# include "mm.h"

MM_DECLARE_HANDLE(mm_mpool_t);

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_mpool_t, mm_mpool_create, (MM_IN mm_mm_t   h_mm,
                                            MM_IN mm_size_t n_element_size));
  MM_FUNCTION(void, mm_mpool_destroy, (MM_IN mm_mpool_t h_mpool));

  MM_FUNCTION(mm_pvoid_t, mm_mpool_borrow, (MM_IN mm_mpool_t h_mpool));
  MM_FUNCTION(void, mm_mpool_return, (MM_IN mm_mpool_t h_mpool,
                                      MM_IN mm_pvoid_t p_element));

  MM_FUNCTION(mm_pvoid_t, mm_mpool_borrow_trace, (MM_IN mm_mpool_t  h_mpool,
                                                  MM_IN mm_string_t sz_file_name,
                                                  MM_IN mm_uint32_t n_line_number));
  MM_FUNCTION(void, mm_mpool_return_trace, (MM_IN mm_mpool_t  h_mpool,
                                            MM_IN mm_pvoid_t  p_element,
                                            MM_IN mm_string_t sz_file_name,
                                            MM_IN mm_uint32_t n_line_number));

# if defined(MM_DEBUG)
#  define MM_MPOOL_BORROW(__handle__)                                   \
  mm_mpool_borrow_trace((__handle__), MM_STRING(__FILE__), __LINE__)

#  define MM_MPOOL_RETURN(__handle__, __element__)                      \
  mm_mpool_return_trace((__handle__), (__element__), MM_STRING(__FILE__), __LINE__)
# else
#  define MM_MPOOL_BORROW(__handle__)           \
  mm_mpool_borrow(__handle__)

#  define MM_MPOOL_RETURN(__handle__, __element__)      \
  mm_mpool_return((__handle__), (__element__))
# endif
  
# if defined(__cplusplus)
}
# endif

#endif /* !__B35687F9AD62F1CBD20BD6162C8__ */
