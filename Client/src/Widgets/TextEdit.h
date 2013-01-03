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

class Graphic::Element;
class Event::Listener;

namespace Widget {
    class Widget;
    class Label;
    
    class TextEdit : public Widget {
    public:
        //! Constructor
        TextEdit(Widget* parent = NULL);
        
        //! Destructor
        ~TextEdit();
        
        //! Constructor with text
        TextEdit(std::string const&, Widget* parent = NULL);
        
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
    };
};


#endif /* defined(__R_Type__TextEdit__) */
