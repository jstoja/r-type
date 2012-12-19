//
//  OpenGL.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef RType_OpenGL_h
# define RType_OpenGL_h

# include <OS.h>

# if defined (OS_WINDOWS)
#  define GLEW_STATIC
#  include <Windows.h>
# endif
# include <GL/glew.h>
# include <SFML/Graphics.hpp>
namespace Graphic {
    
}

#endif
