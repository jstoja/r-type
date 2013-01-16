//
//  WelcomeMenu.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef JOIN_MENU_H
# define JOIN_MENU_H

# include "Menu.h"
# include "IMenuDelegate.h"
# include "Widget/Button.h"
# include "Widget/Label.h"
# include "Widget/Table.h"
# include "Widget/IButtonDelegate.h"
# include "Widget/ITableDelegate.h"

namespace Menu {
    
    class Join : public Menu, public Widget::IButtonDelegate, public Widget::ITableDelegate {
    public:        
        Join(Graphic::Scene *scene, IMenuDelegate* delegate,
                std::string const& serverName);
        virtual ~Join(void);

		void addGame(std::string const& gameName, uint32 gamePlayerNumber, uint32 gamePlayerSlot);

        virtual void buttonReleased(Widget::Button* instance);
        virtual void linePushed(Widget::Table* instance, uint32 line);
      
		virtual void setVisible(bool visible);
    private:
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
