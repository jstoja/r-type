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
    
    //! Class for the Sprite manipulation as Elements
    class Element : public Object {
    public:
       
       	//! Create a new Element
        Element(void);

        //! Create a new Element specifying the Object id
        Element(uint32 id);

        //! Destruct the Element
        virtual ~Element(void);
        
        //! Return the position of the Element
        Vec2 const& getPosition(void) const;

        //! Set the position of the Element
        /*!
         \param position Position vector
         */
        void        setPosition(Vec2 const& position);
        
        //! Return the rotation ratio of the Element
        float32     getRotation(void) const;

        //! Set the rotation ratio of the Element
        /*!
         \param rotation Rotation ratio
         */
        void        setRotation(float32 rotation);
       
       	//! Return the size of the Element
        Vec2 const& getSize(void) const;

        //! Set the size of the Element
        /*!
         \param size Size vector as X and Y size
         */
        void        setSize(Vec2 const& size);
       
       	//! Return the used Sprite of the Element
        Sprite*     getSprite(void) const;

        //! Set the used Sprite of the Element
        /*
         \param sprite Sprite object
         */
        void        setSprite(Sprite* sprite);
        
        //! Return the transformation Matrix
        /*!
         The transformation is calculated with the position and size vectors
         and the rotation ratio
         */
        Matrix4f const& getTransformationMatrix(void);

        //! Return the Rectangle around the Element
        /*!
		 This an be used to detect collision with other Rectangles
		 */
        Rect            getRect(void) const;
        
    private:
        Vec2        _position;
        float32     _rotation;
        Vec2        _size;
        Sprite*     _sprite;
        Matrix4f    _transformationMatrix;
        bool        _updateTransformationMatrix;
    };
    
}

#endif /* defined(__R_Type__Element__) */
