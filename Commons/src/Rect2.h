//
//  Rect.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Rect2__
# define __R_Type__Rect2__

# include <ostream>
# include "Types.h"
# include "Vec2.h"

struct Rect2 {
    
    Rect2(float32 x=0, float32 y=0, float32 width=0, float32 height=0);
    Rect2(Vec2 const& pos, Vec2 const& size);
    ~Rect2();
    
    //! Tests wether a point is in the rect
    bool    in(Vec2 const& point) const;
    
    Vec2    pos;
    Vec2    size;
};

std::ostream& operator<<(std::ostream& stream, Rect2 const& rect);

#endif /* defined(__R_Type__Rect__) */
