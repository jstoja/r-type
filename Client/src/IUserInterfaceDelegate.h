//
//  IUserInterfaceDelegate.h
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//
//

#ifndef R_Type_IUserInterfaceDelegate_h
# define R_Type_IUserInterfaceDelegate_h

# include <string>
# include "Graphic/Scene.h"

class IUserInterfaceDelegate {
public:
    
    virtual ~IUserInterfaceDelegate(void) {};
    
    virtual Graphic::Scene* getScene(void) = 0;
    
    virtual void loginCompleted(std::string const& login,
                                std::string const& ipAdress,
                                std::string const& port) = 0;
    
    virtual void    newGameCompleted(std::string const& name,
                                     uint32 nbPlayers) = 0;    
    virtual void    gameSelected(uint32 gameIndex) = 0;
};

#endif
