//
//  LoginMenu.h
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#ifndef LOGIN_MENU_H
# define LOGIN_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Scene.h"
# include "Widget/Label.h"
# include "Widget/TextEdit.h"
# include "Widget/Button.h"

namespace Menu {
    
    class Login : public Widget::ITextEditDelegate, public Widget::IButtonDelegate {
    public:
        
        Login(Graphic::Scene *scene, IMenuDelegate* delegate);
        virtual ~Login(void);
        
        virtual void textEditFocused(Widget::TextEdit* instance);
        virtual void textEditUnFocused(Widget::TextEdit* instance);
        virtual void textEditHasChanged(Widget::TextEdit* instance);
        
        virtual void buttonHovered(Widget::Button &instance);
        virtual void buttonUnHovered(Widget::Button &instance);
        virtual void buttonPushed(Widget::Button &instance);
        virtual void buttonReleased(Widget::Button &instance);
        
    private:
        Menu::IMenuDelegate*        _delegate;
        Widget::GraphicWidget*      _logoWidget;
        
        Widget::Label*              _ipLabel;
        Widget::TextEdit*           _ipField;
        
        Widget::Label*              _portLabel;
        Widget::TextEdit*           _portField;
        
        Widget::Label*              _usernameLabel;
        Widget::TextEdit*           _usernameField;
        
        Widget::Button*             _connectionButton;
  };
}

#endif
