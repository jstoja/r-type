//
//  WelcomeMenu.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef WELCOME_MENU_H
# define WELCOME_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Scene.h"
# include "Widgets/Widget.h"
# include "Widgets/GraphicWidget.h"
# include "Widgets/Button.h"
# include "Widgets/IButtonDelegate.h"

namespace Menu {
    
    class WelcomeMenu: public Widget::IButtonDelegate {
    public:
        
        static const std::string backgroundImage;
        
        WelcomeMenu(Graphic::Scene *scene, IMenuDelegate* delegate);
        ~WelcomeMenu();

        //! IButtonDelegate Methods
        virtual void buttonHovered(Widget::Button &instance);
        virtual void buttonUnHovered(Widget::Button &instance);
        virtual void buttonPushed(Widget::Button &instance);
        virtual void buttonReleased(Widget::Button &instance);
    private:
        Menu::IMenuDelegate*    _delegate;
        Widget::Button          _button;
    };
    
}

#endif
