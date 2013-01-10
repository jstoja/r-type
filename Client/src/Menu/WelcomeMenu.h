#ifndef WELCOME_MENU_H
# define WELCOME_MENU_H

# include "IMenuDelegate.h"
# include "Graphic/Background.h"

namespace Menu {
  class WelcomeMenu {
    public:
      WelcomeMenu();
      ~WelcomeMenu();

      void                  setBackground(Graphic::Background &background);
      Graphic::Background   &getBackground(void) const;
    private:
      IMenuDelegate         *_delegate;
      Graphic::Background   *_background;
  };
}

#endif
