//
//  WelcomeMenu.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef _GAME_JOIN_MENU_H_
# define _GAME_JOIN_MENU_H_

# include "Menu.h"
# include "IMenuDelegate.h"
# include "Widget/Button.h"
# include "Widget/Label.h"
# include "Widget/Table.h"
# include "Widget/ProgressBar.h"
# include "Widget/IButtonDelegate.h"
# include "Widget/ITableDelegate.h"

namespace Menu {
    
    class GameJoin : public Menu, public Widget::IButtonDelegate {
    public:
        GameJoin(Graphic::Scene *scene, IMenuDelegate* delegate, std::string const& serverName, std::string const& gameName);
        virtual ~GameJoin(void);

		void setProgress(float32 progress);

        virtual void buttonReleased(Widget::Button* instance);
      
		virtual void setVisible(bool visible);

		virtual void setServerName(std::string const& serverName);
    private:
		void	_update();
		Widget::Button*			_previousMenu;
		Widget::Label*			_serverNameLabel;

		Widget::Label*			_joiningGameLabel;
		Widget::Label*			_gameNameLabel;
		Widget::Label*			_joiningStateLabel;
		Widget::GraphicWidget*	_labelsBackground;

		Widget::ProgressBar*	_progressBar;
    };
}

#endif
