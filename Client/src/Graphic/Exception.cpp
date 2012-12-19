//
//  Exception.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "GraphicException.h"

#include "OpenGL.h"

Graphic::Exception::Exception(std::string const& message)
: ::Exception(message, "Graphic Exception") {
}

Graphic::Exception::~Exception() throw() {
}

void Graphic::Exception::checkOpenGLError() {
    GLuint error = glGetError();
    
    if (error == GL_NO_ERROR) return ;
    else if (error == GL_INVALID_ENUM) {
        throw new Graphic::Exception("OpenGL invalid enum");
    } else if (error == GL_INVALID_VALUE) {
        throw new Graphic::Exception("OpenGL invalid value");
    } else if (error == GL_INVALID_OPERATION) {
        throw new Graphic::Exception("OpenGL invalid operation");
    } else if (error == GL_OUT_OF_MEMORY) {
        throw new Graphic::Exception("OpenGL out of memory");
    } else {
        throw new Graphic::Exception("OpenGL error");
    }
}