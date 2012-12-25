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

namespace Widget {
    class Button: public Object {
        public:
            Button(void);
            Button(uint32 id);
            //Button(const std::string &image_path, const Vec2 &pos, const Vec2 &size);
            ~Button();
        
        private:
            Graphic::Element _element;
    };
}

#endif /* defined(__R_Type__Button__) */
