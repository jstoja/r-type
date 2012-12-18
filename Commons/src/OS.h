#ifndef _OS_H_
# define _OS_H_

# if defined(_WIN32)
#  define OS_WINDOWS
# elif defined (__unix__)
#  define OS_UNIX
# endif
# if defined (__APPLE__)
#  define OS_MAC
# endif

#endif
