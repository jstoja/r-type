//
//  Label.h
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#ifndef __R_Type__Label__
# define __R_Type__Label__

# include <iostream>
# include <string>
# include "Widget.h"
# include "Widget/GraphicWidget.h"
# include "Vec3.h"

# ifdef OS_IOS

# else
#  include "Graphic/FreetypeFont.h"
# endif

namespace   Widget {
    class   GraphicWidget;
    
    class   Label : public GraphicWidget {
    public:
        
        enum TextAlignment {
            TextAlignLeft   = 0,
            TextAlignRight  = 1,
            TextAlignCenter = 2
        };
        
        //! Constructor with text
        Label(Graphic::Scene*, std::string const& text="",
              Vec3 color=Vec3(1, 1, 1));
        
        //! Destructor
        ~Label();
        
        //! Update the label with its actual text
        void update();
        
        //! Text getter
        std::string const&  getText() const;

        //! Text setter
        void    setText(std::string const&);
        
        //! Overriding of setter to update font
        virtual void setPosition(Vec3 const&);
        
        //! Overriding of setter to update font
        virtual void setSize(Vec2 const&);
        
        //! Set the text alignment
        void setTextAligment(TextAlignment alignment);
        
        //! Set the text color
        void setColor(Vec3 const& color);
        
    private:
        
        //! Platform specific initialisation of the label
        void _init(void);
        
        //! Platform specific generation of the text texture
        Graphic::Texture* _getStringTexture(void);
        
        //! Platform specific destruction of the label
        void _destroy(void);
        
# ifdef OS_IOS
        void*                           _font;
# else
        Graphic::FreetypeFont*          _font;
# endif
        std::string                     _text;
        TextAlignment                   _alignment;
        Vec3                            _color;
    };
};

#endif /* defined(__R_Type__Label__) */
