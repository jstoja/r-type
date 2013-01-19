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
# include "Menu/GameList.h"
# include "Menu/GamePrepare.h"
# include "Threading/Mutex.h"
# include "Event/IListenerDelegate.h"

class UserInterface : public Menu::IMenuDelegate, public Event::IListenerDelegate {
public:
    
    UserInterface(IUserInterfaceDelegate* delegate);
    ~UserInterface(void);
    
    void update(void);
    
    void presentMessage(std::string const& message);
    void hideMessage(void);
    
    void goToMenu(std::string const& menu);
    
    Menu::Menu* getCurrentMenu(void) const;
    
	void	setServerName(std::string const& serverName);
	void	setGameName(std::string const& gameName);
	void	setGameList(std::list<Game*> const& list);
	void	setCurrentGame(Game* game);
    void	setVisible(bool visible);

    // IListener delegate implementation
    virtual void processEvent(Event::Event const &event);
    
    // IMenuDelegate implementation
    virtual void welcomeCompleted(void);
    virtual void loginCompleted(std::string const& login,
								std::string const& ipAdress,
								std::string const& port);
    virtual void newGameCompleted(std::string const& name, uint32 nbPlayers);
	virtual void createGame(void);
	virtual void joinGame(uint32 idx);
	virtual void previous(void);
    virtual void playerReady(void);

private:
    static const float32 _maxViewportX;

    void _createSceneries(void);
    
    IUserInterfaceDelegate* _delegate;
    Clock                   _time;
    std::string				_serverName;
    
    std::vector<Graphic::Scenery*>      _sceneries;
	std::map<std::string, Menu::Menu*>  _menus;
    Menu::Menu*                         _currentMenu;
    Menu::Menu*                         _nextMenu;
    Widget::Label*                      _messageLabel;
    Threading::Mutex*                   _mutex;
	bool								_visible;
};

#endif /* defined(__R_Type__UserInterface__) */
