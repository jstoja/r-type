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
# include "Event/Manager.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Widget.h"
# include "IButtonDelegate.h"

namespace Widget {
    class Widget;

    class Button : public Widget, public Event::IListenerDelegate {
        public:

            enum framesOrientation {
                VERTICAL,
                HORIZONTAL
            };

            //! Create the Button
            Button(Graphic::Scene*, IButtonDelegate *delegate, Widget* parent = NULL);

            //! Create a button with position/size and image
            Button(Graphic::Scene*,
                    IButtonDelegate *delegate,
                    Vec2 const&,
                    Vec2 const&,
                    std::string const&,
                    Widget* parent = NULL);

            //! Destruct the Button
            ~Button(void);

            // We know the size of the Image, so if we know the orientation and the number of frames, we can split the Image correctly.
            // This will be private but it can be nice to export it to the other classes imo
            uint32  setAutoFrames(uint32 framesNumber, framesOrientation orientation);
            uint32  setManualFrame(const Graphic::Sprite::Frame &frame);

            void    setCurrentFrame(uint32);

            void    draw() {};

            void    update() {};

            // Event Listener Virtual Methods
            virtual void processEvent(Event::Event const& event);

        private:
            Graphic::Element    _element;
            IButtonDelegate     *_delegate;
            Event::Listener     *_eventListener;

    };
}

#endif /* defined(__R_Type__Button__) */
