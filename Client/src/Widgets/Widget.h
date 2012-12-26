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

namespace Widget {
    class Widget : Object {
    public:
        //! Constructor
        Widget(Widget *parent = NULL);

        //! Constructor with id
        Widget(uint32);
        
        //! Destructor
        ~Widget();


        //! Set Widget position
        //void        setPos(WPosition*);
        
        //! Get Widget size
        //WSize*      getSize() const;
        
        //! Set Widget size
        //void        setSize(WSize*);
        
        //! Set focus
        void        setFocus(bool);
        
        //! Get focus
        bool        isFocus() const;
    private:
        Widget*     _parent;
        //WPoint*   _position;
        //WSize*    _size;
        uint32      _x;
        uint32      _y;
        bool        _focus;
    };
}

#endif /* defined(__R_Type__Widget__) */
