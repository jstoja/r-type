//
//  Listener.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Event__Listener__
# define __R_Type__Event__Listener__

# include "Event.h"
# include <cstdlib>

namespace Event {
    
    class IListenerDelegate;
    
    class Listener {
    public:
        Listener(Type type, IListenerDelegate* delegate=NULL);
        
        Type    getType() const;
        void    processEvent(Event const& event);
        
    private:
        Type                _type;
        IListenerDelegate*  _delegate;
    };
    
}

#endif /* defined(__R_Type__Event__Listener__) */
