#ifndef ITEXTEDIT_DELEGATE_H
# define ITEXTEDIT_DELEGATE_H

# include "Widget.h"
# include "TextEdit.h"

namespace Widget {
  class TextEdit;

  class ITextEditDelegate {
    
    public:
      virtual ~ITextEditDelegate() {}

      virtual void textEditFocused(TextEdit* instance) = 0;
      virtual void textEditUnFocused(TextEdit* instance) = 0;
      virtual void textEditHasChanged(TextEdit* instance) = 0;
  };
}

#endif
