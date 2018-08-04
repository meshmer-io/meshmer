#if !defined(__BDACBF28860C077187456FFA7B9__)
# define __BDACBF28860C077187456FFA7B9__

# include "../common/macros.h"
# include "../common/types.h"

MM_DECLARE_HANDLE(mm_mm_t);

# if defined(__cplusplus)
extern "C" {
# endif

  MM_FUNCTION(mm_mm_t, mm_mm_create, (MM_IN mm_mm_t   h_parent,
                                      MM_IN mm_size_t n_quota));
  MM_FUNCTION(void, mm_mm_destroy, (MM_IN mm_mm_t h_mm));

  MM_FUNCTION(mm_pvoid_t, mm_mm_allocate, (MM_IN mm_mm_t   h_mm,
                                           MM_IN mm_size_t n_size));
  MM_FUNCTION(void, mm_mm_free, (MM_IN mm_mm_t    h_mm,
                                 MM_IN mm_pvoid_t p_buffer,
                                 MM_IN mm_size_t  n_size));

  MM_FUNCTION(mm_pvoid_t, mm_mm_allocate_trace, (MM_IN mm_mm_t     h_mm,
                                                 MM_IN mm_size_t   n_size,
                                                 MM_IN mm_string_t sz_file_name,
                                                 MM_IN mm_uint32_t n_line_number));
  MM_FUNCTION(void, mm_mm_free_trace, (MM_IN mm_mm_t     h_mm,
                                       MM_IN mm_pvoid_t  p_buffer,
                                       MM_IN mm_size_t   n_size,
                                       MM_IN mm_string_t sz_file_name,
                                       MM_IN mm_uint32_t n_line_number));

# if defined(MM_DEBUG)
#  define MM_MM_ALLOCATE(__handle__, __size__)                          \
  mm_mm_allocate_trace((__handle__), (__size__), MM_STRING(__FILE__), __LINE__)
  
#  define MM_MM_FREE(__handle__, __buffer__, __size__)                  \
  mm_mm_free_trace((__handle__), (__buffer__), (__size__), MM_STRING(__FILE__), __LINE__)
# else
#  define MM_MM_ALLOCATE(__handle__, __size__)  \
  mm_mm_allocate((__handle__), (__size__))
  
#  define MM_MM_FREE(__handle__, __buffer__, __size__)  \
  mm_mm_free((__handle__), (__buffer__), (__size__))
# endif
  
# if defined(__cplusplus)
}
# endif

#endif /* !__BDACBF28860C077187456FFA7B9__ */
