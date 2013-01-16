#ifndef IBUTTON_DELEGATE_H
#define IBUTTON_DELEGATE_H

# include "Button.h"

namespace Widget {
  class Button;

  class IButtonDelegate {
    public:
      virtual ~IButtonDelegate() {}

      virtual void buttonHovered(Button* instance) {};
      virtual void buttonUnHovered(Button* instance) {};
      virtual void buttonPushed(Button* instance) {};
      virtual void buttonReleased(Button* instance) {};
  };
}

#endif
