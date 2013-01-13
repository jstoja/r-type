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
# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "ICheckBoxDelegate.h"

class Graphic::Element;

namespace Widget {
    class GraphicWidget;
    class IButtonDelegate;
    
    class CheckBox : public GraphicWidget,
                     public Event::IListenerDelegate {
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
                 Vec3 const&,
                 std::string const& = std::string("checkbox.png"),
                 bool checked = false,
                 Widget* parent = NULL);
        
        //! Destructor
        ~CheckBox();
        
                         
        //! Get state
        bool    isChecked() const;
        
        void    update();

        //! Set state
        void    setChecked(bool);
        
        void    setPosition(Vec3 const&);
        
        void    setSize(Vec2 const&);
        
        void    init();

        // IListenerDelegate Virtual Methods
        virtual void processEvent(Event::Event const& event);

    private:
        std::string         _imagePath;
        bool                _checked;
        ICheckBoxDelegate   *_delegate;
        Event::Listener     *_eventListener;
    };
};

#endif /* defined(__R_Type__CheckBox__) */
