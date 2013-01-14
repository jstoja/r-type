//
//  WelcomeMenu.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef WELCOME_MENU_H
# define WELCOME_MENU_H

# include "IMenuDelegate.h"
# include "Widget/Button.h"
# include "Widget/IButtonDelegate.h"

namespace Menu {
    
    class Welcome: public Widget::IButtonDelegate {
    public:
        
        static const std::string backgroundImage;
        
        Welcome(Graphic::Scene *scene, IMenuDelegate* delegate);
        ~Welcome();

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
