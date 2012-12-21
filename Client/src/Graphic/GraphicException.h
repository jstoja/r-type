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
   
   	//! Class to specify graphical exceptions
    class Exception : public ::Exception {
    public:

    	//! Create a new Exception
    	/*!
    	 \param message The message to be printed when the Exception is thrown
    	 */
        Exception(std::string const& message);
        virtual ~Exception() throw();
        
        static void checkOpenGLError();
    };
    
}

#endif /* defined(__RType__Graphic__Exception__) */
