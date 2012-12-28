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
        
        //! Load a letter
        void    loadLetter(uint32);
        
        void    update() {}
        
        void    draw() {}
    private:
        sf::Image       _image;
        std::string     _text;
    };
};

#endif /* defined(__R_Type__Label__) */
