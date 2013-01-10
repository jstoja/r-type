#ifndef ICOMBOBOX_DELEGATE_H
# define ICOMBOBOX_DELEGATE_H

namespace Widget {
  class ComboBox;

  class IComboBoxDelegate {
    public:
      virtual ~IComboBoxDelegate() {}

      virtual void checked(ComboBox &instance) = 0;
      virtual void unchecked(ComboBox &instance) = 0;
  };
}

#endif
