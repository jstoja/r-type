//
//  UserInterface.h
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef __R_Type__UserInterface__
# define __R_Type__UserInterface__

# include "IUserInterfaceDelegate.h"
# include "Clock.h"
# include "Menu/IMenuDelegate.h"
# include "Menu/WelcomeMenu.h"

class UserInterface : public Menu::IMenuDelegate {
public:
    
    UserInterface(IUserInterfaceDelegate* delegate);
    ~UserInterface(void);
    
    void update(void);
    
    // IMenuDelegate implementation
    virtual void welcomeCompleted(void);
    virtual void newGameCallGeneralMenu(void);
    virtual void serverListCallGeneralMenu(void);
    virtual void optionsCallGeneralMenu(void);

    
private:
    static const float32 _maxViewportX;
    void _createSceneries(void);
    
    IUserInterfaceDelegate* _delegate;
    Clock                   _time;
    Menu::WelcomeMenu*      _welcomeMenu;
    
    std::vector<Graphic::Scenery*>  _sceneries;
};

#endif /* defined(__R_Type__UserInterface__) */
