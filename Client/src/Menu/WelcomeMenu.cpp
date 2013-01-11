#include "WelcomeMenu.h"

Menu::WelcomeMenu::WelcomeMenu(Graphic::Scene *scene, IMenuDelegate* delegate)
: _delegate(delegate),
  _button(scene, this, scene->getViewport(), scene->getViewport()/2.0, WELCOME_MENU_BACKGROUND) {
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
