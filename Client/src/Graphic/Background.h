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
    
    class Background : public Object {
    public:
        
        Background(void);
        Background(uint32 id);
        virtual ~Background();
        
        Vec2 const& getRange(void) const;
        void        setRange(Vec2 const& range);
        
        float32     getRepeat(void) const;
        void        setRepeat(float32 repeat);
        
    private:
        Texture*    _texture;
        Vec2        _range;
        float32     _repeat;
    };
    
}

#endif /* defined(__R_Type__Background__) */
