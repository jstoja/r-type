//
//  Listener.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Event__Listener__
# define __R_Type__Event__Listener__

# include <cstdlib>
# include "Event.h"
# include "Rect2.h"

namespace Event {
    
    class IListenerDelegate;
    
    class Listener {
    public:
        Listener(uint32 type, IListenerDelegate* delegate=NULL);
        Listener(uint32 type, Rect2 const& rect, IListenerDelegate* delegate=NULL);
        
        Type            getType() const;
        Rect2 const&    getRect() const;
        void            setRect(Rect2 const& rect);
        bool            hasRect() const;
        void            processEvent(Event const& event);
        
    private:
        Type                _type;
        IListenerDelegate*  _delegate;
        Rect2                _rect;
        bool                _hasRect;
    };
    
}

#endif /* defined(__R_Type__Event__Listener__) */
