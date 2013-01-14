//
//  UserInterface.h
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef __R_Type__UserInterface__
# define __R_Type__UserInterface__

# include <string>
# include "IUserInterfaceDelegate.h"
# include "Clock.h"
# include "Menu/IMenuDelegate.h"
# include "Menu/Welcome.h"
# include "Menu/Login.h"

class UserInterface : public Menu::IMenuDelegate {
public:
    
    UserInterface(IUserInterfaceDelegate* delegate);
    ~UserInterface(void);
    
    void update(void);
    
    // IMenuDelegate implementation
    virtual void welcomeCompleted(void);
    virtual void loginCompleted(std::string const& login,
								std::string const& ipAdress,
								std::string const& port);
    virtual void newGameCallGeneralMenu(void);
    virtual void serverListCallGeneralMenu(void);
    virtual void optionsCallGeneralMenu(void);

    
private:
    static const float32 _maxViewportX;
    void _createSceneries(void);
    
    IUserInterfaceDelegate* _delegate;
    Clock                   _time;
    
    std::vector<Graphic::Scenery*>  _sceneries;
    
    // Menus
    Menu::Welcome*                  _welcomeMenu;
    Menu::Login*                    _loginMenu;
};

#endif /* defined(__R_Type__UserInterface__) */
