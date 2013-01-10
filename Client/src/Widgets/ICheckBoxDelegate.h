#ifndef ICHECKBOX_DELEGATE_H
# define ICHECKBOX_DELEGATE_H

# include "Widget.h"
# include "CheckBox.h"

namespace Widget {
  class CheckBox;

  class ICheckBoxDelegate {

    public:
      virtual ~ICheckBoxDelegate() {}

      virtual void checked(CheckBox &instance) = 0;
      virtual void unchecked(CheckBox &instance) = 0;
  };
}

#endif
