//
//  Texture.h
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#ifndef __RType__Texture__
# define __RType__Texture__

# include "OS.h"

# ifndef OS_IOS
#  include <SFML/Graphics.hpp>
# endif
# include "OpenGL.h"
# include "Types.h"
# include "Object.h"

namespace Graphic {
    
    //! Class for manipulation of OpenGL textures
    class Texture : public Object {
    public:
        
        //! Create a new texture
        Texture();
        
        //! Create a new texture with a given id
        Texture(uint32 id);
        
        //! Destruct the texture
        virtual ~Texture();
        
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

        //! Set the data of the texture from an image file
        void    setDataFromFile(std::string const& fileName);
        
        //! Return the internal OpenGL id of the texture
        uint32  getGLID() const;
        
    private:
        GLuint  _glID;
    };
    
}

#endif /* defined(__RType__Texture__) */
