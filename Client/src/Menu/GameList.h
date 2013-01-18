//
//  GameList.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef _GAME_LIST_MENU_H_
# define _GAME_LIST_MENU_H_

# include "Menu.h"
# include "IMenuDelegate.h"
# include "Widget/Button.h"
# include "Widget/Label.h"
# include "Widget/Table.h"
# include "Widget/IButtonDelegate.h"
# include "Widget/ITableDelegate.h"
# include "../Game.h"

namespace Menu {
    
    class GameList : public Menu, public Widget::IButtonDelegate, public Widget::ITableDelegate {
    public:        
        GameList(Graphic::Scene *scene, IMenuDelegate* delegate);
        virtual ~GameList(void);

		void setGameList(std::list<Game*> const& gameList);

        virtual void buttonReleased(Widget::Button* instance);
        virtual void linePushed(Widget::Table* instance, uint32 line);
      
		virtual void setVisible(bool visible);
		virtual void setServerName(std::string const& serverName);
    private:
		void	_addGame(std::string const& gameName, uint32 gamePlayerNumber, uint32 gamePlayerSlot);
		void	_updatePageButtons();

		Widget::Label*      _serverNameLabel;

		Widget::Button*		_previousMenu;

		Widget::Table*		_gameList;

		Widget::Button*		_nextPageButton;
		Widget::Button*		_previousPageButton;
		Widget::Button*		_createGame;
    };
}

#endif
