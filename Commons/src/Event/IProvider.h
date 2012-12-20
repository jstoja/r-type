//
//  IProvider.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef R_Type_Event_IProvider_h
#define R_Type_Event_IProvider_h

namespace Event {
    
    class Manager;
    
    class IProvider {
    public:
        virtual ~IProvider() {};
        
        virtual void processEvents(Manager* manager) = 0;
    };
}

#endif
