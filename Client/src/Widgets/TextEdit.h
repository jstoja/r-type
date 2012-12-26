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
    
    class TextEdit : protected Widget {
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
        
        //! Setter position
        void setPosition(const Vec2 &position);

        //! Setter size
        void setSize(const Vec2 &size);
        
        //! Getter position
        Vec2 const &getPosition(void) const;

        //! Getter size
        Vec2 const &getSize(void) const;
        
        Graphic::Element *getElement();
    private:
        Event::Listener     _event;
        Graphic::Element    _element;
        std::string         _text;
        Vec2                _size;
        Vec2                _position;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
