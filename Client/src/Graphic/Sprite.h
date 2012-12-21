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
# include "Graphic/Texture.h"
# include "Graphic/Buffer.hpp"

namespace Graphic {
    
    class Sprite : public Object {
    public:
        
        struct Frame {
            
            Frame(Vec2 const& p1, Vec2 const& p2);
            
            Vec2    p1;
            Vec2    p2;
        };
        
        Sprite();
        Sprite(uint32 id);
        virtual ~Sprite();
        
        Texture*    getTexture() const;
        void        setTexture(Texture* texture);
        
        void            addFrame(Frame const& frame);
        Frame const&    getFrame(uint32 index);
        
        Bufferf*        getTexuteCoordsBuffer(void);
        
    private:
        Texture*            _texture;
        std::vector<Frame>  _frames;
        Bufferf*            _textureCoords;
        bool                _needRebuildTextureCoords;
    };
    
}

#endif /* defined(__R_Type__Sprite__) */
