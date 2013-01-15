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

# include <OS.h>
# include "Event.h"
# include "Rect2.h"

namespace Event {
    
    class IListenerDelegate;
    
    class COMMON_EXPORT_IMPORT Listener {
    public:
        Listener(uint32 type, IListenerDelegate* delegate=NULL);
        Listener(uint32 type, Rect2 const& rect, IListenerDelegate* delegate=NULL);
		virtual ~Listener();
        
        Type            getType() const;
        Rect2 const&    getRect() const;
        void            setRect(Rect2 const& rect);
        bool            hasRect() const;
        void            processEvent(Event const& event);
		void			deleteLater();
        bool			shouldBeDeleted() const;

    private:
        Type                _type;
        IListenerDelegate*  _delegate;
        Rect2                _rect;
        bool                _hasRect;
		bool				_delete;
    };
    
}

#endif /* defined(__R_Type__Event__Listener__) */
