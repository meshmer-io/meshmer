#if !defined(__E689D7347E115D2801C17954FE7__)
# define __E689D7347E115D2801C17954FE7__

# if defined(__cplusplus)
#  define MM_DEFINE_DATA_TYPE(__base__, __name__)                       \
  typedef __base__ __name__, *p##__name__, &r##__name__;                \
  typedef const __base__ c##__name__, *pc##__name__, &rc##__name__
# else
#  define MM_DEFINE_DATA_TYPE(__base__, __name__)                       \
  typedef __base__ __name__, *p##__name__;                              \
  typedef const __base__ c##__name__, *pc##__name__
# endif

# define MM_DECLARE_DATA_TYPE(__type__, __name__)       \
  __type__ __name__;                                    \
  MM_DEFINE_DATA_TYPE(__type__ __name__, __name__)

# define MM_DECLARE_ENUM(__name__)   MM_DEFINE_DATA_TYPE(enum __name__, __name__)
# define MM_DECLARE_UNION(__name__)  MM_DECLARE_DATA_TYPE(union, __name__)
# define MM_DECLARE_STRUCT(__name__) MM_DECLARE_DATA_TYPE(struct, __name__)

# if defined(__cplusplus)
#  define MM_DECLARE_CLASS(__name__) MM_DECLARE_DATA_TYPE(class, __name__)
# endif

# define MM_DECLARE_HANDLE(__name__)            \
  MM_DECLARE_STRUCT(_##__name__);               \
  MM_DEFINE_DATA_TYPE(p_##__name__, __name__)

# define MM_DEFINE_STRUCT(__name__, __body__)   \
  MM_DECLARE_STRUCT(__name__);                  \
  struct __name__ __body__

# define MM_DEFINE_HANDLE(__name__, __body__)   \
  MM_DECLARE_HANDLE(__name__);                  \
  struct _##__name__ __body__

# if defined(MM_MSVC)
#  include "msvc/macros.h"
# else
#  error MMCE01: Unsupported toolchain
# endif

# define MM_STATIC_FUNCTION(__result__, __function_name__, __parameters__) \
  static MM_INTERNAL_FUNCTION(__result__, __function_name__, __parameters__)

# define MM_STATIC_CDECL_FUNCTION(__result__, __function_name__, __parameters__) \
  static MM_INTERNAL_CDECL_FUNCTION(__result__, __function_name__, __parameters__)

# if defined(MM_X86)
#  define MM_DECLARE_SINGLE_ALIGNED_STRUCT(__name__)    \
  MM_DECLARE_ALIGNED_STRUCT(4, __name__)

#  define MM_DECLARE_DOUBLE_ALIGNED_STRUCT(__name__)    \
  MM_DECLARE_ALIGNED_STRUCT(8, __name__)

#  define MM_DEFINE_SINGLE_ALIGNED_STRUCT(__name__, __body__)   \
  MM_DEFINE_ALIGNED_STRUCT(4, __name__, __body__)

#  define MM_DEFINE_DOUBLE_ALIGNED_STRUCT(__name__, __body__)   \
  MM_DEFINE_ALIGNED_STRUCT(8, __name__, __body__)
# elif defined(MM_X86_64)
#  define MM_DECLARE_SINGLE_ALIGNED_STRUCT(__name__)    \
  MM_DECLARE_ALIGNED_STRUCT(8, __name__)

#  define MM_DECLARE_DOUBLE_ALIGNED_STRUCT(__name__)    \
  MM_DECLARE_ALIGNED_STRUCT(16, __name__)

#  define MM_DEFINE_SINGLE_ALIGNED_STRUCT(__name__, __body__)   \
  MM_DEFINE_ALIGNED_STRUCT(8, __name__, __body__)

#  define MM_DEFINE_DOUBLE_ALIGNED_STRUCT(__name__, __body__)   \
  MM_DEFINE_ALIGNED_STRUCT(16, __name__, __body__)
# else
#  error MMCE02: Unsupported platform
# endif

#endif /* !__E689D7347E115D2801C17954FE7__ */
