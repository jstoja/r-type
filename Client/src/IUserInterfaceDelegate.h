//
//  IUserInterfaceDelegate.h
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//
//

#ifndef R_Type_IUserInterfaceDelegate_h
# define R_Type_IUserInterfaceDelegate_h

# include "Graphic/Scene.h"

class IUserInterfaceDelegate {
public:
    
    virtual ~IUserInterfaceDelegate(void) {};
    
    virtual Graphic::Scene* getScene(void) = 0;
    
};

#endif
