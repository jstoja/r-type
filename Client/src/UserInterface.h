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
# include <map>

# include "IUserInterfaceDelegate.h"
# include "Clock.h"
# include "Menu/IMenuDelegate.h"
# include "Widget/Label.h"
# include "Menu/Welcome.h"
# include "Menu/Login.h"
# include "Menu/NewGame.h"
# include "Menu/Join.h"
# include "Menu/GamePrepare.h"

class UserInterface : public Menu::IMenuDelegate {
public:
    
    UserInterface(IUserInterfaceDelegate* delegate);
    ~UserInterface(void);
    
    void update(void);
    
    void presentMessage(std::string const& message);
    void hideMessage(void);
    
    // IMenuDelegate implementation
    virtual void welcomeCompleted(void);
    virtual void loginCompleted(std::string const& login,
								std::string const& ipAdress,
								std::string const& port);
    virtual void newGameCompleted(std::string const& name, uint32 nbPlayers);
	virtual void createGame();
	virtual void joinGame(uint32 idx);
	virtual void previous();
    
private:
    static const float32 _maxViewportX;
    void _createSceneries(void);
    
    IUserInterfaceDelegate* _delegate;
    Clock                   _time;
    
    std::vector<Graphic::Scenery*>  _sceneries;
	std::map<std::string, Menu::Menu*>	_menus;
    Menu::Menu*                     _currentMenu;
    Widget::Label*                  _messageLabel;
};

#endif /* defined(__R_Type__UserInterface__) */
