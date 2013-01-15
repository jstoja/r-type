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

namespace Menu {
    
    class Login : public Widget::ITextEditDelegate {
    public:
        
        Login(Graphic::Scene *scene, IMenuDelegate* delegate);
        virtual ~Login(void);
        
        virtual void textEditFocused(Widget::TextEdit* instance);
        virtual void textEditUnFocused(Widget::TextEdit* instance);
        virtual void textEditHasChanged(Widget::TextEdit* instance);
        
    private:
        Menu::IMenuDelegate*        _delegate;
        std::vector<Widget::Label*> _labels;
        Widget::TextEdit*           _ipField;
  };
}

#endif
