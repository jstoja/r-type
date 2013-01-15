//
//  TextEdit.h
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#ifndef __R_Type__TextEdit__
# define __R_Type__TextEdit__

# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "GraphicWidget.h"
# include "Widget/Label.h"
# include "ITextEditDelegate.h"

namespace Event {
    class Manager;
    class Listener;
    class IListenerDelegate;
};

namespace Widget {
    class GraphicWidget;
    class Label;
    class ITextEditDelegate;
    
    class TextEdit : public GraphicWidget,
                     public Event::IListenerDelegate {
    public:
        //! Constructor
        TextEdit(Graphic::Scene* scene,
                 ITextEditDelegate * delegate,
                 std::string const& background);
        
        //! Destructor
        ~TextEdit();
        
        //! Getter text
        std::string const&   getText() const;

        //! Setter text
        void    setText(std::string const&);
        
        //! Draw
        void    draw() {}
        
        //! Put a char in string
        void    operator<<(char);
        
        //! Put a string in string
        void    operator<<(std::string const&);
        
        //! Init the text edit
        void    init();
        
        //! Clear text
        void    clear();
        
        //! Set position
        void    setPosition(Vec3 const&);
        
        //! Overlead of process event
        virtual void    processEvent(Event::Event const&);
    private:
        Event::Listener*    _eventListener;
        Label               _label;
        ITextEditDelegate*  _delegate;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
