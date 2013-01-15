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
    
    class TextEdit : public GraphicWidget, public Event::IListenerDelegate {
    public:
        //! Constructor
        TextEdit(Graphic::Scene* scene,
                 ITextEditDelegate * delegate,
                 std::string const& background);
        
        //! Destructor
        ~TextEdit();
        
        //! Return the value of the text input
        std::string const&   getValue() const;

        //! Set the field value
        void    setValue(std::string const&);
        
        //! Draw
        void    draw() {}
                
        //! Init the text edit
        void    init();
        
        //! Set position
        void    setPosition(Vec3 const&);
                         
         //! Set size
         void    setSize(Vec2 const&);
        
        //! Overload of process event
        virtual void processEvent(Event::Event const&);
        
        //! Overload of set focus to handle iOS input
        virtual void setFocus(bool);
        
    private:
        Event::Listener*    _eventListener;
        Label               _label;
        ITextEditDelegate*  _delegate;
        int32               _labelMaxLength;
        std::string         _value;
    };
};


#endif /* defined(__R_Type__TextEdit__) */
