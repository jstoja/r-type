//
//  Manager.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Event__Manager__
# define __R_Type__Event__Manager__

# include <vector>
# include <list>

# include <OS.h>
# include "Singleton.hpp"
# include "Event.h"
# include "IProvider.h"
# include "Listener.h"
# include "Vec2.h"

namespace Event {
    
    class COMMON_EXPORT_IMPORT Manager : public Singleton<Manager> {
        friend class Singleton<Manager>;
        
    public:
        void registerProvider(IProvider* provider);
        void addEventListener(Listener* listener);
        void removeEventListener(Listener* listener);
        
        void processEvents(void);
        void fire(Event const& event);
        
    private:
		void _flushListeners();

        Manager(void);
        ~Manager(void);
        
        std::vector<IProvider*>*	_providers;
        std::vector<Listener*>*		_listeners;
        Vec2						_lastPointerPos;
		int							_isInListenerLoop;
        std::list<Listener*>*		_listenersToRemove;
        std::list<Listener*>*		_listenersToAdd;
    };
    
}

#endif /* defined(__R_Type__Event__Manager__) */
