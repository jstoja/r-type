//
//  Texture.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__Texture__
# define __RType__Texture__

# include "OpenGL.h"
# include "Types.h"

namespace Graphic {
    
    //! Class for manipulation of OpenGL textures
    class Texture {
    public:
        
        //! Create a new texture
        Texture();
        
        //! Destruct the texture
        ~Texture();
        
        //! Binds the texture
        /*!
         Binding a texture make it the 'current texture' for all following
         OpenGL operations
         */
        void    bind();
        
        //! Set the data of the texture
        /*!
         Data must contain width * height pixels encoded in RGBA, 32bpp
         */
        void    setData(uint32 width, uint32 height, const uint8* data);
        
        //! Return the internal OpenGL id of the texture
        uint32  getId() const;
        
    private:
        GLuint  _id;
    };
    
}

#endif /* defined(__RType__Texture__) */
