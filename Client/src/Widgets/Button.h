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
# include "Object.h"
# include "Graphic/Element.h"
# include "Widget.h"

namespace Widget {
    class Button : public Widget {
        public:
        
            enum framesOrientation {
                VERTICAL,
                HORIZONTAL
            };
        
            //! Create the Button
            Button(void);
        
            //! Create the Button with the specified Object id
            Button(uint32 id);
        
            //! Destruct the Button
            ~Button(void);
            // This method will be private after, it will be used to load a default image
            bool    loadImage(const std::string &image_path);

            // We know the size of the Image, so if we know the orientation and the number of frames, we can split the Image correctly.
            // This will be private but it can be nice to export it to the other classes imo
            uint32  setAutoFrames(uint32 framesNumber, framesOrientation orientation);
            uint32  setManualFrame(const Graphic::Sprite::Frame &frame);
        
            Graphic::Element *getElement();
        private:
            Graphic::Element    _element;
        
    };
}

#endif /* defined(__R_Type__Button__) */
