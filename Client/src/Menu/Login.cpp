//
//  LoginMenu.cpp
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "Menu/Login.h"

Menu::Login::Login(Graphic::Scene *scene, IMenuDelegate* delegate) :
_delegate(delegate) {
    
    _ipField = new Widget::TextEdit(scene, this, "text-field.png");
    _ipField->setText("hello!");
    
    /*
    Widget::Label* label;
    label = new Widget::Label(scene, "Server IP", Vec3((float32)0x56/0xff, (float32)0xa2/0xff, (float32)0x6f/0xff));
    label->setTextAligment(Widget::Label::TextAlignCenter);
    label->setPosition(Vec3(scene->getViewport().x, scene->getViewport().y)
                          / 2);
    label->setSize(Vec2(scene->getViewport().x, 1));
    _labels.push_back(label);
     */
}

Menu::Login::~Login(void) {
    for (std::vector<Widget::Label*>::iterator it = _labels.begin(),
         end = _labels.end(); it != end; ++it)
        delete *it;
}

void Menu::Login::textEditFocused(Widget::TextEdit* instance) {
    Log("Focused");
}

void Menu::Login::textEditUnFocused(Widget::TextEdit* instance) {
    Log("UnFocused");
}

void Menu::Login::textEditHasChanged(Widget::TextEdit* instance) {
    
}