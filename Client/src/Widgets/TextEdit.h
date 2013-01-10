//
//  TextEdit.h
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#ifndef __R_Type__TextEdit__
# define __R_Type__TextEdit__

# include <iostream>
# include "ITextEditDelegate.h"

class Graphic::Element;
class Event::Listener;

namespace Graphic {
    class Scene;
};

namespace Widget {
    class Widget;
    class Label;
    
    class TextEdit : public Widget {
    public:
        //! Constructor
        TextEdit(Graphic::Scene*,
                 Widget* parent = NULL);
        
        //! Destructor
        ~TextEdit();
        
        //! Constructor with text
        TextEdit(Graphic::Scene*,
                 std::string const&,
                 Widget* parent = NULL);
        
        //! Getter text
        std::string const&   getText() const;

        //! Setter text
        void    setText(std::string const&);
        
        void    draw() {}
        
        void    update();
        
        void    operator<<(char);
        
        void    operator<<(std::string const&);
        
        void    init();
        
        void    clear();
        
        void    setPosition(Vec2 const&);
        
    private:
        Event::Listener     _event;
        Label               _label;
        ITextEditDelegate   *_delegate;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
