#if !defined(__3E3B18BFEE37176A503784100DC__)
# define __3E3B18BFEE37176A503784100DC__

# include "macros.h"

# if defined(MM_MSVC)
#  include "msvc/types.h"
# else
#  error MMCE01: Unsupported toolchain
# endif

typedef void *pmm_void_t;
MM_DEFINE_DATA_TYPE(pmm_void_t, mm_pvoid_t);

enum mm_bool_t { mm_false = 0, mm_true = 1 };
MM_DECLARE_ENUM(mm_bool_t);

MM_DEFINE_DATA_TYPE(mm_uint8_t,  mm_byte_t  );
MM_DEFINE_DATA_TYPE(mm_uint16_t, mm_port_t  );
MM_DEFINE_DATA_TYPE(mm_uint32_t, mm_result_t);
MM_DEFINE_DATA_TYPE(mm_uint64_t, mm_size_t  );

# if defined(MM_X86)
MM_DEFINE_DATA_TYPE(mm_uint32_t, mm_word_t);
# elif defined(MM_X86_64)
MM_DEFINE_DATA_TYPE(mm_uint64_t, mm_word_t);
# else
#  error MMCE02: Unsupported platform
# endif

#endif /* !__3E3B18BFEE37176A503784100DC__ */
