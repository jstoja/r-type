//
//  WelcomeMenu.cpp
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "WelcomeMenu.h"

#ifdef OS_IOS
const std::string Menu::WelcomeMenu::backgroundImage = "welcome-screen-ios.png";
#else
const std::string Menu::WelcomeMenu::backgroundImage = "welcome-screen.png";
#endif

Menu::WelcomeMenu::WelcomeMenu(Graphic::Scene *scene, IMenuDelegate* delegate)
: _delegate(delegate),
  _button(scene, this, scene->getViewport(),
          Vec3(scene->getViewport().x,
               scene->getViewport().y)
          / 2.0, backgroundImage)
{
      Graphic::Sprite *sprite = _button.getSprite();
      sprite->clearFrames();
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
}

Menu::WelcomeMenu::~WelcomeMenu() {
}

void Menu::WelcomeMenu::buttonHovered(Widget::Button &instance) {
}

void Menu::WelcomeMenu::buttonUnHovered(Widget::Button &instance) {
}
void Menu::WelcomeMenu::buttonPushed(Widget::Button &instance) {

}
void Menu::WelcomeMenu::buttonReleased(Widget::Button &instance) {
    _delegate->welcomeCompleted();
}
