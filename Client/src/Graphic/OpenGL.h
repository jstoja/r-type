//
//  OpenGL.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef RType_OpenGL_h
# define RType_OpenGL_h

# include "OS.h"

# if defined (OS_IOS)
#  include <OpenGLES/ES2/gl.h>
# else
#   include <GL/glew.h>
#   if defined(OS_WINDOWS)
#       include <GL/wglew.h>
#   endif
# endif

namespace Graphic {
    
}

#endif
