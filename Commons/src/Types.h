#ifndef _TYPES_H_
# define _TYPES_H_

# include <OS.h>

# if defined(OS_WINDOWS)
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
# elif defined(OS_UNIX)
#  include <stdint.h>
# endif

#endif
