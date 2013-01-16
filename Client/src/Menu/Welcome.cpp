//
//  Welcome.cpp
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "Welcome.h"

#include "Graphic/Scene.h"

#ifdef OS_IOS
const std::string Menu::Welcome::backgroundImage = "welcome-screen-ios.png";
#else
const std::string Menu::Welcome::backgroundImage = "welcome-screen.png";
#endif

Menu::Welcome::Welcome(Graphic::Scene *scene, IMenuDelegate* delegate)
: Menu(scene, delegate),
  _button(scene, this, backgroundImage)
{
    _button.setSize(scene->getViewport());
    _button.setPosition(Vec3(scene->getViewport().x,
                             scene->getViewport().y)
                        / 2.0);
      Graphic::Sprite *sprite = _button.getSprite();
      sprite->clearFrames();
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
      sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 1.0)));
}

Menu::Welcome::~Welcome() {    
}

void Menu::Welcome::buttonHovered(Widget::Button* instance) {
}

void Menu::Welcome::buttonUnHovered(Widget::Button* instance) {
}
void Menu::Welcome::buttonPushed(Widget::Button* instance) {

}
void Menu::Welcome::buttonReleased(Widget::Button* instance) {
    getDelegate()->welcomeCompleted();
}
