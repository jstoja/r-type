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
    
    _logoWidget = new Widget::GraphicWidget(scene, "logo.png");
    _logoWidget->setSize(Vec2(11.7, 3.2));
    _logoWidget->setPosition(Vec3(scene->getViewport().x/2,
                                  scene->getViewport().y - 1.6));
    
    
    // Setup form
    
    _ipLabel = new Widget::Label(scene, "Server IP");
    _ipLabel->setTextAligment(Widget::Label::TextAlignRight);
    _ipLabel->setSize(Vec2(4.8, 0.525));
    _ipLabel->setPosition(Vec3(scene->getViewport().x/2 - 3.2,
                          4.9, 0));
    
    _ipField = new Widget::TextEdit(scene, this, "text-field.png");
    _ipField->setValue("");
    _ipField->setSize(Vec2(6.5, 1.25));
    _ipField->setPosition(Vec3(scene->getViewport().x/2 + 2.6,
                               4.9, 0));
    
    _portLabel = new Widget::Label(scene, "Server PorT");
    _portLabel->setTextAligment(Widget::Label::TextAlignRight);
    _portLabel->setSize(Vec2(4.8, 0.525));
    _portLabel->setPosition(Vec3(scene->getViewport().x/2 - 3.2,
                               3.7, 0));
    
    _portField = new Widget::TextEdit(scene, this, "text-field.png");
    _portField->setValue("");
    _portField->setSize(Vec2(6.5, 1.25));
    _portField->setPosition(Vec3(scene->getViewport().x/2 + 2.6,
                               3.7, 0));
    
    
    _usernameLabel = new Widget::Label(scene, "Username");
    _usernameLabel->setTextAligment(Widget::Label::TextAlignRight);
    _usernameLabel->setSize(Vec2(4.8, 0.525));
    _usernameLabel->setPosition(Vec3(scene->getViewport().x/2 - 3.2,
                                 2.5, 0));
    
    _usernameField = new Widget::TextEdit(scene, this, "text-field.png");
    _usernameField->setValue("");
    _usernameField->setSize(Vec2(6.5, 1.25));
    _usernameField->setPosition(Vec3(scene->getViewport().x/2 + 2.6,
                                 2.5, 0));
    
    _connectionButton = new Widget::Button(scene, this, "button-connection.png");
    _connectionButton->setSize(Vec2(4.9, 0.85));
    _connectionButton->setPosition(Vec3(scene->getViewport().x/2, 1));
}

Menu::Login::~Login(void) {
    delete _logoWidget;
    delete _ipLabel;
    delete _ipField;
    delete _portLabel;
    delete _portField;
    delete _usernameLabel;
    delete _usernameField;
    delete _connectionButton;
}

void Menu::Login::textEditFocused(Widget::TextEdit* instance) {
    
}

void Menu::Login::textEditUnFocused(Widget::TextEdit* instance) {
    
}

void Menu::Login::textEditHasChanged(Widget::TextEdit* instance) {
    
}

void Menu::Login::buttonHovered(Widget::Button &instance) {
    
}

void Menu::Login::buttonUnHovered(Widget::Button &instance) {
    
}

void Menu::Login::buttonPushed(Widget::Button &instance) {
    
}

void Menu::Login::buttonReleased(Widget::Button &instance) {
    if (_ipField->getValue() != "" && _portField->getValue() != ""
        && _usernameField->getValue() != "") {
        _delegate->loginCompleted(_usernameField->getValue(), _ipField->getValue(), _portField->getValue());
    }
}