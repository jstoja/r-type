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
# include "Vec3.h"

struct COMMON_EXPORT_IMPORT Vec2 {
    
    Vec2(float32 x=0.0, float32 y=0.0);
    Vec2(Vec3 const& v);
    
    bool operator>=(Vec2 const& v2) const;
    bool operator<=(Vec2 const& v2) const;
    Vec2 operator+(Vec2 const& v2) const;
    Vec2 operator-(Vec2 const& v2) const;
    Vec2 operator/(Vec2 const& v2) const;
    Vec2 operator*(Vec2 const& v2) const;
    
    Vec2 operator/(float32 v2) const;
    Vec2 operator*(float32 v2) const;
    
    bool operator==(Vec2 const& v2) const;
    bool operator!=(Vec2 const& v2) const;
    
    float32 x;
    float32 y;
};

std::ostream& operator<<(std::ostream& stream, Vec2 const& v);

#endif /* defined(__R_Type__Vec2__) */
