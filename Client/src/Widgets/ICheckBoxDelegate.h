#ifndef ICHECKBOX_DELEGATE_H
# define ICHECKBOX_DELEGATE_H

# include "Widget.h"
# include "CheckBox.h"

namespace Widget {
  class CheckBox;

  class ICheckBoxDelegate {

    public:
      virtual ~ICheckBoxDelegate() {}

      virtual CheckBox *checked() = 0;
      virtual CheckBox *unchecked() = 0;
  };
}

#endif
