#ifndef WELCOME_MENU_H
# define WELCOME_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Background.h"

# define WELCOME_MENU_BACKGROUND "background_menu.png"

namespace Menu {
  class WelcomeMenu {
    public:
      WelcomeMenu(IMenuDelegate* delegate);
      ~WelcomeMenu();

      /*void                  setBackground(Graphic::Background &background);
      Graphic::Background   &getBackground(void) const;*/
    private:
      Menu::IMenuDelegate         *_delegate;
      Graphic::Background         _background;
  };
}

#endif
