//
//  Background.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Graphic__Background__
# define __R_Type__Graphic__Background__

# include "Object.h"
# include "Texture.h"
# include "Vec2.h"

namespace Graphic {
    class Texture;
    
    //! Class for using a texture as Background
    class Background : public Object {
    public:

        //! Create a new Background
        Background(void);

        //! Create a new Background specifying the Object id
        Background(uint32 id);

        //! Destruct the Background
        virtual ~Background();
        
        //! Set the background texture
        void    setTexture(Texture* texture);
        
        //! Get the background texture
        Texture*    getTexture(void) const;
        
        //! Return the range used for the Background
        Vec2 const& getRange(void) const;
        //! Set the range of the background
        void        setRange(Vec2 const& range);
        
        //! Return the repeat ratio of the Background
        float32     getRepeat(void) const;
        //! Set the repeat ratio of the Background
        void        setRepeat(float32 repeat);
        
        //! Set the background opacity
        void        setOpacity(float32 opacity);
        
        //! Get the background opacity
        float32     getOpacity(void);
        
    private:
        Graphic::Texture*    _texture;
        Vec2                _range;
        float32             _repeat;
        float32             _opacity;
    };
    
}

#endif /* defined(__R_Type__Background__) */
