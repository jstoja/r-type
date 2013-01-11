#include "WelcomeMenu.h"

Menu::WelcomeMenu::WelcomeMenu(Menu::IMenuDelegate* delegate)
: _delegate(delegate) {
  Graphic::Texture *tex = new Graphic::Texture();
  std::string fileName(WELCOME_MENU_BACKGROUND);

  tex->setDataFromFile(fileName);
  _background.setTexture(tex);
}
