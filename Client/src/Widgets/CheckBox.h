//
//  CheckBox.h
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#ifndef __R_Type__CheckBox__
# define __R_Type__CheckBox__

# include <iostream>
# include "ICheckBoxDelegate.h"
# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"

namespace Widget {
    class Widget;
    class Button;
    
    class CheckBox : public Widget, public Event::IListenerDelegate {
    public:
        //! Constructor
        CheckBox(Graphic::Scene*,
                 ICheckBoxDelegate *delegate,
                 bool checked = false,
                 Widget* parent = NULL);
        
        //! Constructor
        CheckBox(Graphic::Scene*,
                 ICheckBoxDelegate *delegate,
                 Vec2 const&,
                 Vec2 const&,
                 std::string const& = std::string("checkbox.png"),
                 bool checked = false,
                 Widget* parent = NULL);
        
        //! Destructor
        ~CheckBox();
        
        //! Getter state
        bool    isChecked() const;
        
        //! Setter state
        void    setChecked(bool);
        
        void    draw() {}
        
        //! Update when state button change
        void    update();
        
        void    setPosition(Vec2 const&);
        
        void    setSize(Vec2 const&);
        
        void    init();

        // IListenerDelegate Virtual Methods
        virtual void processEvent(Event::Event const& event);
    private:
        std::string         _imagePath;
        bool                _checked;
        Button              _button;
        ICheckBoxDelegate   *_delegate;
        Event::Listener     *_eventListener;
    };
};

#endif /* defined(__R_Type__CheckBox__) */
