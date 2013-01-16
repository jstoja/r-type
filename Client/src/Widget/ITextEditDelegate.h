#ifndef ITEXTEDIT_DELEGATE_H
# define ITEXTEDIT_DELEGATE_H

# include "Widget.h"
# include "TextEdit.h"

namespace Widget {
  class TextEdit;

  class ITextEditDelegate {
    
    public:
      virtual ~ITextEditDelegate() {}

      virtual void textEditFocused(TextEdit* instance) {};
      virtual void textEditUnFocused(TextEdit* instance) {};
      virtual void textEditHasChanged(TextEdit* instance) {};
  };
}

#endif
