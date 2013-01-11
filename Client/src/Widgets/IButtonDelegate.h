#ifndef IBUTTON_DELEGATE_H
#define IBUTTON_DELEGATE_H

# include "Button.h"

namespace Widget {
  class Button;

  class IButtonDelegate {
    public:
      virtual ~IButtonDelegate() {}

      virtual void buttonClicked(Button &instance) = 0;

      /*
      virtual void buttonHovered(Button &instance) = 0;
      virtual void buttonPushed(Button &instance) = 0;
      virtual void buttonReleased(Button &instance) = 0;
      */
  };
}

#endif
