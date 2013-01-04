//
//  Widget.h
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#ifndef __R_Type__Widget__
# define __R_Type__Widget__

# include <iostream>
# include "Object.h"
# include "UUIDGenerator.h"
# include "Types.h"
# include "OS.h"
# include "Graphic/Element.h"

struct Vec2;

namespace Graphic {
    class Scene;
};

namespace Widget {
    
    class Widget {

        public:
            //! Constructor
            Widget(Graphic::Scene*, Widget* parent = NULL);

            //! Destructor
            virtual ~Widget();
        
            //! Scene setter
            void    setScene(Graphic::Scene*);
        
            //! Add element in scene
            void    addElement();
        
            //! Scene getter
            Graphic::Scene*     getScene() const;
        
            //! Pos getter
            Vec2 const&         getPosition() const;
            
            //! Get Widget size
            Vec2 const&         getSize() const;
        
            //! Get element size
            Vec2 const&         getElementSize() const;
        
            //! Set Widget position
            virtual void        setPosition(Vec2 const&);
            
            //! Set Widget size
            virtual void        setSize(Vec2 const&);
            
            //! Set focus
            virtual void        setFocus(bool);
        
            //! Get focus
            bool                hasFocus() const;
            
            //! Get Element
            Graphic::Element    *getElement();
        
            //! Draw virtual method
            virtual void        draw() = 0;
        
            //! Update virtual method
            virtual void        update() = 0;
        
            //! Load image of the Element with the image specified in the image_path parameter
            bool                loadImage(const std::string &image_path);
        
            //! Parent widget getter
            Widget* getParent() const;
    protected:
            Graphic::Scene*     _scene;
            Widget*             _parent;
            Graphic::Element    _element;
            Vec2                _size;
            Vec2                _position;
            bool                _focus;
    };
}

#endif /* defined(__R_Type__Widget__) */
