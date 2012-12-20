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
# include "Rect.h"

namespace Event {
    
    enum Type {
        Close,
        PointerIn,
        PointerOut,
        PointerMove
    };
    
    struct Event {
    public:
        Event(Type type, IProvider* sender=NULL);
        Event(Type type, Rect const& rect, IProvider* sender=NULL);
        
        Type        type;
        IProvider*  sender;
        Rect        rect;
    };
}

#endif /* defined(__R_Type__Event__Event__) */
