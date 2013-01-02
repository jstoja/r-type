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

# include <ft2build.h>
# include FT_FREETYPE_H
# include <freetype/freetype.h>
# include <freetype/ftglyph.h>
# include <freetype/ftoutln.h>
# include <freetype/fttrigon.h>


namespace Graphic {
    class  FreetypeFont;
};

namespace   Widget {
    class   Widget;
    
    class   Label : public Widget {
    public:
        //! Constructor
        Label();
        
        //! Constructor with text
        Label(std::string const&);
        
        //! Destructor
        ~Label();
        
        //! Text getter
        std::string const&  getText() const;

        //! Text setter
        void    setText(std::string const&);
        
        //! Init label, load alphabet image
        void    init();
        
        //! Add a letter in wod
        void    operator<<(char);
        
        //! Contact
        void    operator<<(std::string const&);
     
        void    clear();
        
        void    update();
        
        void    draw() {}
    private:
        Graphic::FreetypeFont   _font;
        sf::Image               _image;
        std::string             _text;
    };
};

#endif /* defined(__R_Type__Label__) */
