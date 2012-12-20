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

# include "Singleton.hpp"
# include "Event.h"
# include "IProvider.h"
# include "Listener.h"

namespace Event {
    
    class Manager : public Singleton<Manager> {
        friend class Singleton<Manager>;
        
    public:
        void registerProvider(IProvider* provider);
        void addEventListener(Listener* listener);
        
        void processEvents();
        void fire(Event const& event);
        
    private:
        Manager();
        ~Manager();
        
        std::vector<IProvider*> _providers;
        std::vector<Listener*>  _listeners;
    };
    
}

#endif /* defined(__R_Type__Event__Manager__) */
