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
# include "Vec3.h"
# include "Rect2.h"
# include "Matrix.hpp"

namespace Graphic {
    
    //! Class for the Sprite manipulation as Elements
    class Element : public Object {
    public:
        
        //! Element types
        enum Type {
            Static,
            /*! Static element, often part of the backround, that scrolls with
                the viewport */
            Dynamic,
            /* An element that move often, like a missile or ship */
            Floating
            /* A fixed interface element that doesn't move with the viewport */
        };
       
       	//! Create a new Element
        Element(void);

        //! Create a new Element specifying the Object id
        Element(uint32 id);

        //! Destruct the Element
        virtual ~Element(void);
        
        //! Get the type of the element
        Type        getType(void) const;
        
        //! Set the type of the element
        void        setType(Type type);
        
        //! Return the position of the Element
        Vec3 const& getPosition(void) const;

        //! Set the position of the Element
        /*!
         \param position Position vector
         */
        void        setPosition(Vec3 const& position);
        
        //! Return the rotation ratio of the Element
        float32     getRotation(void) const;

        //! Set the rotation ratio of the Element
        /*!
         \param rotation Rotation ratio
         */
        void        setRotation(float32 rotation);
        
        //! Set the element opacity
        void        setOpacity(float32 opacity);
        
        //! Get the element opacity
        float32     getOpacity(void);
       
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

        //! Return the current Sprite frame used
        uint16      getCurrentFrame(void) const;

        //! Set the Sprite frame to be used
        /*!
         \param frame The frame number
         */
        void        setCurrentFrame(uint16 frame);
        
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
        Rect2            getRect(void) const;
        
    private:
        Type        _type;
        Vec3        _position;
        float32     _rotation;
        float       _opacity;
        Vec2        _size;
        Sprite*     _sprite;
        uint16      _currentFrame;
        Matrix4f    _transformationMatrix;
        bool        _updateTransformationMatrix;
    };
    
}

#endif /* defined(__R_Type__Element__) */
