#ifndef ITEXTEDIT_DELEGATE_H
# define ITEXTEDIT_DELEGATE_H

# include "Widget.h"
# include "TextEdit.h"

namespace Widget {
  class TextEdit;

  class ITextEditDelegate {
    
    public:
      virtual ~ITextEditDelegate() {}

      virtual void textClicked(TextEdit &instance) = 0;
      virtual void textHasChanged(TextEdit &instance) = 0;
  };
}

#endif
