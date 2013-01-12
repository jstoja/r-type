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
# include "Graphic/FreetypeFont.h"
# include "Widget.h"

namespace   Widget {
    class   GraphicWidget;
    
    class   Label : public GraphicWidget {
    public:
        //! Constructor
        Label(Graphic::Scene*,
              Widget* parent = NULL);
        
        //! Constructor with text
        Label(Graphic::Scene*,
              std::string const&,
              Widget* parent = NULL);
        
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
        static Graphic::FreetypeFont   *_font;
        std::string             _text;
    };
};

#endif /* defined(__R_Type__Label__) */
