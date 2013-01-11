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
# include "Graphic/FreetypeFont.h"
# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "ITextEditDelegate.h"

namespace Event {
    class Manager;
    class Listener;
    class IListenerDelegate;
};

namespace Widget {
    class Widget;
    class Label;
    class ITextEditDelegate;
    
    class TextEdit : public Widget,
                     public Event::IListenerDelegate {
    public:
        //! Constructor
        TextEdit(Graphic::Scene*,
                 ITextEditDelegate *,
                 Widget* parent = NULL);
        
        //! Destructor
        ~TextEdit();
        
        //! Constructor with text
        TextEdit(Graphic::Scene*,
                 ITextEditDelegate*,
                 std::string const&,
                 Widget* parent = NULL);
        
        //! Getter text
        std::string const&   getText() const;

        //! Setter text
        void    setText(std::string const&);
        
        //! Draw
        void    draw() {}
        
        //! Update
        void    update();
        
        //! Put a char in string
        void    operator<<(char);
        
        //! Put a string in string
        void    operator<<(std::string const&);
        
        //! Init the text edit
        void    init();
        
        //! Clear text
        void    clear();
        
        //! Set position
        void    setPosition(Vec2 const&);
        
        //! Overlead of process event
        virtual void    processEvent(Event::Event const&);
    private:
        Event::Listener*    _eventListener;
        Label               _label;
        ITextEditDelegate*  _delegate;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
