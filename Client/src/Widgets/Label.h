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
# include "GraphicWidget.h"

# ifdef OS_IOS

# else
#  include "Graphic/FreetypeFont.h"
# endif

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
                
        //! Add a letter in wod
        void    operator<<(char);
        
        //! Concat
        void    operator<<(std::string const&);
     
        void    clear();
        
        //! Platform specific update of the label with its actual text
        void    update();
        
    private:
        
        //! Platform specific initialisation of the label
        void _init(void);
        
# ifdef OS_IOS
        
# else
        static Graphic::FreetypeFont*   _font;
# endif
        std::string                     _text;
    };
};

#endif /* defined(__R_Type__Label__) */
