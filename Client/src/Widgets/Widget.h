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

        //! Set Widget position
        virtual void        setPosition(Vec2 const&);
                
        //! Pos getter
        Vec2 const& getPosition() const;
        
        //! Get Widget size
        Vec2 const& getSize() const;
        
        //! Set Widget size
        virtual void        setSize(Vec2 const&);
        
        //! Set focus
        virtual void        setFocus(bool);
        
        //! Get focus
        bool        isFocus() const;
    protected:
        Widget*     _parent;
        Vec2        _size;
        Vec2        _position;
        uint32      _x;
        uint32      _y;
        bool        _focus;
    };
}

#endif /* defined(__R_Type__Widget__) */
