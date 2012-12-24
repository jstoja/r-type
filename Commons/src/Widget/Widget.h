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
# include "UUIDGenerator.h"
# include "Types.h"
# include "OS.h"

class Widget {
public:
    //! Constructor
    Widget(Widget *parent = NULL);

    //! Destructor
    ~Widget();
    
    //! Get id of Widget
    uint32  getId() const;
    
    //! Get Widget position
    //WPoint*  getPos() const;

    //! Set Widget position
    //void        setPos(WPosition*);

    //! Get Widget size
    //WSize*      getSize() const;

    //! Set Widget size
    //void        setSize(WSize*);

    //! Set focus
    void        setFocus(bool);

    //! Get focus
    bool        isFocus();
private:
    Widget*     _parent;
    //WPosition*  _position;
    //WSize*      _size;
    uint32      _id;
    uint32      _x;
    uint32      _y;
    bool        _focus;
};

#endif /* defined(__R_Type__Widget__) */
