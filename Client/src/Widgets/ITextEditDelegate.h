#ifndef ITEXTEDIT_DELEGATE_H
# define ITEXTEDIT_DELEGATE_H

# include "Widget.h"
# include "TextEdit.h"

namespace Widget {
  class TextEdit;

  class ITextEditDelegate {
    
    public:
      virtual ~ITextEditDelegate() {}

      virtual TextEdit *textHasChanged() = 0;
  };
}

#endif
