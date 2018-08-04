#if !defined(__035BC919A83FBD2987A9931E440__)
# define __035BC919A83FBD2987A9931E440__

# if defined(MM_KERNEL)
# else
#  include <windows.h>
#  include <tchar.h>
# endif

# define MM_IN    _In_
# define MM_OUT   _Out_
# define MM_INOUT _Inout_

# define MM_CALLBACK(__result__, __callback_name__, __parameters__)     \
  typedef __result__ (__stdcall *__callback_name__) __parameters__

# define MM_CDECL_CALLBACK(__result__, __callback_name__, __parameters__) \
  typedef __result__ (__cdecl *__callback_name__) __parameters__

# define MM_INTERNAL_FUNCTION(__result__, __function_name__, __parameters__) \
  __result__ __stdcall __function_name__ __parameters__

# define MM_INTERNAL_CDECL_FUNCTION(__result__, __function_name__, __parameters__) \
  __result__ __cdecl __function_name__ __parameters__

# if defined(MM_SHARED_OBJECT)
#  define MM_FUNCTION(__result__, __function_name__, __parameters__)    \
  __declspec(dllexport) MM_INTERNAL_FUNCTION(__result__, __function_name__, __parameters__)

#  define MM_CDECL_FUNCTION(__result__, __function_name__, __parameters__) \
  __declspec(dllexport) MM_INTERNAL_CDECL_FUNCTION(__result__, __function_name__, __parameters__)
# elif defined(MM_USE_SHARED_OBJECT)
#  define MM_FUNCTION(__result__, __function_name__, __parameters__)    \
  __declspec(dllimport) MM_INTERNAL_FUNCTION(__result__, __function_name__, __parameters__)
  
#  define MM_CDECL_FUNCTION(__result__, __function_name__, __parameters__) \
  __declspec(dllimport) MM_INTERNAL_CDECL_FUNCTION(__result__, __function_name__, __parameters__)
# else
#  define MM_FUNCTION(__result__, __function_name__, __parameters__)    \
  MM_INTERNAL_FUNCTION(__result__, __function_name__, __parameters__)

#  define MM_CDECL_FUNCTION(__result__, __function_name__, __parameters__) \
  MM_INTERNAL_CDECL_FUNCTION(__result__, __function_name__, __parameters__)
# endif

# define MM_STRING(__text__) _T(__text__)

# define MM_DECLARE_ALIGNED_STRUCT(__alignment__, __name__)             \
  MM_DECLARE_DATA_TYPE(__declspec(align(__alignment__)) struct, __name__)

# define MM_DEFINE_ALIGNED_STRUCT(__alignment__, __name__, __body__)    \
  MM_DECLARE_ALIGNED_STRUCT(__alignment__, __name__);                   \
  __declspec(align(__alignment__)) struct __name__ __body__

#endif /* !__035BC919A83FBD2987A9931E440__ */
