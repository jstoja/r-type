//
//  Sprite.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Sprite__
# define __R_Type__Sprite__

# include <vector>
# include "Object.h"
# include "Vec2.h"
# include "Texture.h"
# include "Buffer.hpp"

namespace Graphic {
    
    //! Class modelizing a Sprite (a Texture with Frames)
    class Sprite : public Object {
    public:
        
        //! Definition of a Frame
        struct Frame {
            
            //! Create a Frame with ???
            Frame(Vec2 const& p1, Vec2 const& p2);
            
            Vec2    p1;
            Vec2    p2;
        };

        enum FramesOrientation {
            Vertical,
            Horizontal
        };
        
        //! Create a Sprite
        Sprite();

        //! Create a Sprite with a specified Object id
        Sprite(uint32 id);

        //! Destroy the Sprite
        virtual ~Sprite();
        
        //! We know the size of the Image,
        //! so if we know the orientation and the number of frames,
        //! we can set automatically all frames.
        void    setAutoFrames(uint32 framesNumber, Sprite::FramesOrientation orientation=Vertical);

        void    clearFrames();

        //! Return the Sprite's Texture
        Texture*    getTexture() const;

        //! Set the Sprite's Texture
        void        setTexture(Texture* texture);
        
        //! Add a new Frame to the Sprite
        void            addFrame(Frame const& frame);

        //! Return the Frame linked to the Sprite
        Frame const&    getFrame(uint32 index);
        
        //! Return the coordinates of the Sprite's Texture
        Bufferf*        getTexuteCoordsBuffer(void);
        
    private:
        Texture*            _texture;
        std::vector<Frame>  _frames;
        Bufferf*            _textureCoords;
        bool                _needRebuildTextureCoords;
    };
    
}

#endif /* defined(__R_Type__Sprite__) */
