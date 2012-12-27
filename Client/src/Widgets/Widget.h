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

class Vec2;

namespace Widget {
    
    class Widget : Object {

        public:
            //! Constructor
            Widget(Widget *parent = NULL);
            
            //! Constructor with id
            Widget(uint32);
            
            //! Destructor
            virtual ~Widget();
            
            //! Pos getter
            Vec2 const&         getPosition() const;
            
            //! Get Widget size
            Vec2 const&         getSize() const;
            
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
        
            //! Load image of the Element with the image specified in the image_path parameter
            bool                loadImage(const std::string &image_path);
        protected:
            Widget*             _parent;
            Graphic::Element    _element;
            Vec2                _size;
            Vec2                _position;
            bool                _focus;
    };
}

#endif /* defined(__R_Type__Widget__) */
