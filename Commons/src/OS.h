#ifndef _OS_H_
# define _OS_H_

# if defined(_WIN32)
#  define OS_WINDOWS
# elif defined (__APPLE__)
#  define OS_MAC
# endif
# if (defined __unix__ || defined OS_MAC)
#  define OS_UNIX
# endif
#endif
