//
//  Button.h
//  R-Type
//
//  Created by Julien Bordellier on 25/12/12.
//
//

#ifndef __R_Type__Button__
# define __R_Type__Button__

# include <iostream>
# include <string>
# include "Vec2.h"
# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "IButtonDelegate.h"

namespace Widget {
    class GraphicWidget;
    class IButtonDelegate;

    class Button : public GraphicWidget, public Event::IListenerDelegate {
        public:
            //! Create the Button
            Button(Graphic::Scene*,
                   IButtonDelegate *delegate,
                   Widget* parent = NULL);

            //! Create a button with position/size and image
            Button(Graphic::Scene*,
                    IButtonDelegate *delegate,
                    Vec2 const&,
                    Vec2 const&,
                    std::string const&,
                    Widget* parent = NULL);

            //! Destruct the Button
            ~Button(void);

            void    setCurrentFrame(uint32);

        
            virtual void setPosition(Vec2 const &pos);
            virtual void setSize(Vec2 const &size);
        
            // Event Listener Virtual Methods
            virtual void processEvent(Event::Event const& event);

        private:
            IButtonDelegate     *_delegate;
            Event::Listener     *_eventListener;

    };
}

#endif /* defined(__R_Type__Button__) */
