//
//  Event.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Event__Event__
# define __R_Type__Event__Event__

# include <cstdlib>
# include "IProvider.h"
# include "Vec2.h"

namespace Event {
    
    enum Type {
        Close           =   1 << 1,
        PointerIn       =   1 << 2,
        PointerOut      =   1 << 3,
        PointerMove     =   1 << 4,
        PointerPushed   =   1 << 5,
        PointerReleased =   1 << 6
    };
    
    enum PointerButton {
        PointerLeft     =   0,
        PointerRight    =   1,
        PointerMiddle   =   2
    };
    
    struct Event {
    public:
        Event(Type type, IProvider* sender=NULL);
        Event(Type type, Vec2 const& pos, IProvider* sender=NULL);
        
        Type            type;
        IProvider*      sender;
        Vec2            pos;
        PointerButton   pointerButton;
    };
}

#endif /* defined(__R_Type__Event__Event__) */
