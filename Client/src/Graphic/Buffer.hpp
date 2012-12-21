//
//  Buffer.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__Buffer__
# define __RType__Buffer__

# include "OpenGL.h"
# include "GraphicException.h"
# include "Types.h"

namespace Graphic {
    
    //! Class for manipulation of OpenGL Buffers    
    template<class T>
    class Buffer {
    public:
        
        //! Buffer types
        /*!
         Define the different possible types for a buffer
         */
        enum Type {
            VertexArray = GL_ARRAY_BUFFER,
            /*! Vertex array buffer, to store an array of vertex attributes */
            ElementArray = GL_ELEMENT_ARRAY_BUFFER,
            /*! Element array buffer, to store an array of vertex indices */
        };
        
        //! Buffer usages
        /*!
         Define the different kinds of usage for a buffer.
         Usage is provided as a performance hint for opengl, it does not constraint
         the actual usage of the buffer.
         */        
        enum Usage {
            StaticDraw = GL_STATIC_DRAW
            /*! Usage for a buffer modified by the application and used by OpenGL
             for drawing */
        };
        
        //! Create a buffer
        /*!
         \param type Buffer type
         \param usage Buffer usage type
         */        
        Buffer(Type type, Usage usage=StaticDraw) :
            _id(0), _type(type), _usage(usage) {
            glGenBuffers(1, &_id);
        }
        
        //! Destruct a buffer
        ~Buffer() {
            glDeleteBuffers(1, &_id);
        }
        
        //! Bind a buffer
        /*!
         Binding a buffer make it the 'current buffer' for all OpenGL operations
         on its Type of buffer.
         */
        void bind() const {
            glBindBuffer(_type, _id);
        }
        
        //! Set the buffer data
        /*!
         Update the buffer data with values pointed by 'data'
         \param data Must point to a valid memory space of the specified size
         \param size Size of the data
         */
        void setData(const T* data, uint32 size) {
            bind();
            _size = size;
            glBufferData(_type, _size * sizeof(T), data, _usage);
            Graphic::Exception::checkOpenGLError();
        }
        
        //! Set a part of the buffer data
        /*!
         Update the data range defined by 'offset' and 'offset + size'
         with values pointed by 'data'
         \param data Must point to a valid memory space which size is at least
         'size'
         \param offset Start of the range to set
         \param size Size of the range to set
         */        
        void setData(const T* data, GLintptr offset, GLsizeiptr size) {
            bind();
            glBufferSubData(_type, offset * sizeof(T), size * sizeof(T), data);
            Graphic::Exception::checkOpenGLError();
        }

        //! Returns the internal OpenGL id of the buffer
        uint32 getId() const {
            return _id;
        }
        
        //! Returns the size of the buffer
        uint32 getSize() const {
            return _size;
        }
        
    private:
        GLuint  _id;
        Type    _type;
        Usage   _usage;
        uint32  _size;
    };
    
    typedef Buffer<GLfloat> Bufferf;
    typedef Buffer<GLuint>  Bufferui;

}

#endif /* defined(__RType__Buffer__) */
