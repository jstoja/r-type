//
//  IListenerDelegate.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef R_Type_Event_IListenerDelegate_h
# define R_Type_Event_IListenerDelegate_h

# include "Event.h"

namespace Event {
    
    class IListenerDelegate {
    public:
        virtual ~IListenerDelegate() {};
        
        virtual void processEvent(Event const& event) = 0;
    };
    
}

#endif
