#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT 8

#ifdef LONG_MAX
# ifdef LONG_MAX == INT32_MAX
#  define LONG_BIT 32
# else
// Safe assumption
#  define LONG_BIT 64
# endif
#elif defined __LONG_MAX__
# if __LONG_MAX__ == INT32_MAX
#  define LONG_BIT 32
# else
// Safe assumption
#  define LONG_BIT 64
# endif
#else
# error "Unsupported configuration, please define either LONG_MAX or __LONG_MAX__"
#endif

#undef LLONG_MAX
#undef ULLONG_MAX
#define LLONG_MIN (-__LONG_LONG_MAX__ - 1LL)
#define LLONG_MAX __LONG_LONG_MAX__
#define ULLONG_MAX (__LONG_LONG_MAX__ * 2ULL + 1ULL)

#define NAME_MAX 255
#define PATH_MAX 4096
#define LINE_MAX 4096
#define PIPE_BUF 4096

// This value is a guaranteed minimum, get the current maximum from sysconf
#define NGROUPS_MAX 8

#if INTPTR_MAX == INT64_MAX
# define SSIZE_MAX LONG_MAX
#elif INTPTR_MAX == INT32_MAX
# define SSIZE_MAX INT_MAX
#endif

#define _POSIX_ARG_MAX 4096
#define _POSIX_OPEN_MAX 16
#define _POSIX_HOST_NAME_MAX 255

#define PTHREAD_STACK_MIN 16384

#define UCHAR_MAX 0xff
#define USHORT_MAX 0xffff
#define UINT_MAX 0xffffffffu
#define ULONG_MAX 0xfffffffffffffffful
#define INT_MAX 0x7fffffff
#define INT_MIN -0x80000000
#define LONG_MAX 0x7fffffffffffffffl
#define LONG_MIN -0x8000000000000000l

#endif // _LIMITS_H
