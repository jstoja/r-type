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
    
    class TextEdit : public Widget {
    public:
        //! Constructor
        TextEdit();
        
        //! Destructor
        ~TextEdit();
        
        //! Constructor with text
        TextEdit(std::string const&);
        
        //! Getter text
        std::string const&   getText() const;

        //! Setter text
        void    setText(std::string const&);
        
        //! Setter text
        void    setText(const char *);
        
        void    draw() {}
        
        void    update() {}
        
    private:
        Event::Listener     _event;
        std::string         _text;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
