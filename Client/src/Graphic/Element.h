//
//  Element.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Graphic__Element__
# define __R_Type__Graphic__Element__

# include "Object.h"
# include "Sprite.h"
# include "Types.h"
# include "Vec2.h"
# include "Rect.h"
# include "Matrix.hpp"

namespace Graphic {
    
    class Element : public Object {
    public:
        
        Element(void);
        Element(uint32 id);
        virtual ~Element(void);
        
        Vec2 const& getPosition(void) const;
        void        setPosition(Vec2 const& position);
        
        float32     getRotation(void) const;
        void        setRotation(float32 rotation);
        
        Vec2 const& getSize(void) const;
        void        setSize(Vec2 const& size);
        
        Sprite*     getSprite(void) const;
        void        setSprite(Sprite* sprite);
        uint16      getCurrentFrame(void) const;
        void        setCurrentFrame(uint16 frame);
        
        Matrix4f const& getTransformationMatrix(void);
        Rect            getRect(void) const;
        
    private:
        Vec2        _position;
        float32     _rotation;
        Vec2        _size;
        Sprite*     _sprite;
        uint16      _currentFrame;
        Matrix4f    _transformationMatrix;
        bool        _updateTransformationMatrix;
    };
    
}

#endif /* defined(__R_Type__Element__) */
