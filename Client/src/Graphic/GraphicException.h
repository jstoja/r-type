//
//  Exception.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__Graphic__Exception__
# define __RType__Graphic__Exception__

# include "Exception.h"

namespace Graphic {
    
    class Exception : public ::Exception {
    public:
        Exception(std::string const& message);
        virtual ~Exception() throw();
        
        static void checkOpenGLError();
    };
    
}

#endif /* defined(__RType__Graphic__Exception__) */
