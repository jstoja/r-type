#ifndef IBUTTON_DELEGATE_H
#define IBUTTON_DELEGATE_H

# include "Widget.h"
# include "Button.h"

namespace Widget {
  class Button;

  class IButtonDelegate {
    public:
      virtual ~IButtonDelegate() {}

      virtual void buttonClicked(Button &instance) = 0;
      //virtual Widget::Button *buttonHover() = 0;
  };
}

#endif
