#ifndef ICOMBOBOX_DELEGATE_H
# define ICOMBOBOX_DELEGATE_H

namespace Widget {
  class ComboBox;

  class IComboBoxDelegate {
    public:
      virtual ~IComboBoxDelegate() {}

      virtual ComboBox *checked() = 0;
      virtual ComboBox *unchecked() = 0;
  };
}

#endif
