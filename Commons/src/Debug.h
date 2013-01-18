//
//  Debug.h
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#ifndef __R_Type__Debug__
# define __R_Type__Debug__

# include <iostream>
# include <string>

# include <OS.h>

# define DEBUG_ENABLED

# ifdef DEBUG_ENABLED
# include <iomanip>
#  define Log(x) (*Debug::logStream << x << std::endl)
# else
#  define Log(x) {}
# endif

class COMMON_EXPORT_IMPORT Debug {
public:
    
    static std::ostream* logStream;
    
};

#endif /* defined(__R_Type__Debug__) */
