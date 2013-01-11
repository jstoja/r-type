//
//  IProvider.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef R_Type_Event_IProvider_h
# define R_Type_Event_IProvider_h

# include <OS.h>

namespace Event {
    
    class Manager;
    
    class COMMON_EXPORT_IMPORT_REMOVED IProvider {
    public:
        inline virtual ~IProvider() {};
        
        virtual void processEvents(Manager* manager) = 0;
    };
}

#endif
