#if !defined(__ED3E5D794E146435B3D748B2C76__)
# define __ED3E5D794E146435B3D748B2C76__

MM_DEFINE_DATA_TYPE(char,                   mm_int8_t  );
MM_DEFINE_DATA_TYPE(unsigned char,          mm_uint8_t );
MM_DEFINE_DATA_TYPE(short int,              mm_int16_t );
MM_DEFINE_DATA_TYPE(unsigned short int,     mm_uint16_t);
MM_DEFINE_DATA_TYPE(int,                    mm_int32_t );
MM_DEFINE_DATA_TYPE(unsigned int,           mm_uint32_t);
MM_DEFINE_DATA_TYPE(long long int,          mm_int64_t );
MM_DEFINE_DATA_TYPE(unsigned long long int, mm_uint64_t);

MM_DEFINE_DATA_TYPE(unsigned long long int volatile, mm_volatile_uint64_t);
MM_DEFINE_DATA_TYPE(__declspec(align(8)) unsigned long long int volatile, mm_aligned_uint64_t);
MM_DEFINE_DATA_TYPE(void volatile *, mm_volatile_pvoid_t);

# if defined(MM_UNICODE)
MM_DEFINE_DATA_TYPE(wchar_t,   mm_char_t  );
MM_DEFINE_DATA_TYPE(wchar_t *, mm_string_t);
# else
MM_DEFINE_DATA_TYPE(char,   mm_char_t  );
MM_DEFINE_DATA_TYPE(char *, mm_string_t);
# endif

#endif /* !__ED3E5D794E146435B3D748B2C76__ */
