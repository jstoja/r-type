//
//  Vec2.h
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#ifndef __R_Type__Vec2__
# define __R_Type__Vec2__

# include <ostream>
# include "Types.h"

struct Vec2 {
    
    Vec2(float32 x=0.0, float32 y=0.0);
    
    float32 x;
    float32 y;
};

bool operator>=(Vec2 const& v1, Vec2 const& v2);
bool operator<=(Vec2 const& v1, Vec2 const& v2);
Vec2 operator+(Vec2 const& v1, Vec2 const& v2);

std::ostream& operator<<(std::ostream& stream, Vec2 const& v);

#endif /* defined(__R_Type__Vec2__) */
