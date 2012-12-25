//
//  WPoint.h
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#ifndef __R_Type__WPoint__
# define __R_Type__WPoint__

# include <iostream>
# include "OS.h"
# include "Types.h"

namespace Widget {
    class Point {
    public:
        //! Constructor
        Point();
    
        //! Constructor with coord
        Point(uint32, uint32);
    
        //! Copy constructor
        Point(Point const&);
    
        //! Destructor
        ~Point();
    
        //! Get x pos
        uint32  x() const;
    
        //! Get y pos
        uint32  y() const;
    
        //! Set x pos
        void    setX(uint32);
        
        //! Set y pos
        void    setY(uint32);

        //! Assignation
        Point  operator=(Point const&);

        //! Comparaison
        bool    operator==(Point const&) const;

        //! Comaparaison
        bool    operator!=(Point const&) const;
    private:
        uint32  _x;
        uint32  _y;
    };
}

#endif /* defined(__R_Type__WPoint__) */
