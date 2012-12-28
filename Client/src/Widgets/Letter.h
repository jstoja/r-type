//
//  Letter.h
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#ifndef __R_Type__Letter__
#define __R_Type__Letter__

# include <iostream>

namespace   Widget {
    
    class   Widget;
    
    class   Letter : public Widget {
    public:
        //! Constructor
        Letter();
    
        //! Destructor
        ~Letter();

        //! Load a letter
        void    loadLetter(sf::Image const&);
    };
};


#endif /* defined(__R_Type__Letter__) */
