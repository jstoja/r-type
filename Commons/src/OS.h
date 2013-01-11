//
// OS.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:22 2012 Samuel Olivier
//

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

# if (defined OS_MAC)
#  include <TargetConditionals.h>
#  if TARGET_OS_IPHONE
#   define OS_IOS
#  endif
# endif

# ifdef OS_WINDOWS
#  ifdef COMMON_EXPORT
#    define COMMON_EXPORT_IMPORT __declspec(dllexport)
#    define COMMON_EXPORT_IMPORT_REMOVED __declspec(dllexport)
#  else
#    define COMMON_EXPORT_IMPORT __declspec(dllimport)
#    define COMMON_EXPORT_IMPORT_REMOVED
#  endif
# else
#  define COMMON_EXPORT_IMPORT_REMOVED
#  define COMMON_EXPORT_IMPORT
# endif

#endif