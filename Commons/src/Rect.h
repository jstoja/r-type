//
//  Rect.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Rect__
# define __R_Type__Rect__

# include <ostream>
# include "Types.h"
# include "Vec2.h"

struct Rect {
    
    Rect(float32 x=0, float32 y=0, float32 width=0, float32 height=0);
    ~Rect();
    
    //! Tests wether a point is in the rect
    bool    in(Vec2 const& point) const;
    
    Vec2    pos;
    Vec2    size;
};

std::ostream& operator<<(std::ostream& stream, Rect const& rect);

#endif /* defined(__R_Type__Rect__) */