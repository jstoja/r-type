//
// Vec3.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 16:07:35 2013 Samuel Olivier
//

#ifndef _VECT_3_H_
# define _VECT_3_H_

# include <ostream>
# include "Types.h"

struct COMMON_EXPORT_IMPORT Vec3 {
    
    Vec3(float32 x=0.0, float32 y=0.0, float32 z=0.0);
    
    bool operator>=(Vec3 const& v3) const;
    bool operator<=(Vec3 const& v3) const;
    Vec3 operator+(Vec3 const& v3) const;
    Vec3 operator-(Vec3 const& v3) const;
    Vec3 operator/(Vec3 const& v3) const;
    Vec3 operator*(Vec3 const& v3) const;
    
    Vec3 operator/(float32 v3) const;
    Vec3 operator*(float32 v3) const;
    
    bool operator==(Vec3 const& v3) const;
    bool operator!=(Vec3 const& v3) const;
    
    float32 x;
    float32 y;
    float32 z;
};

std::ostream& operator<<(std::ostream& stream, Vec3 const& v);

#endif /* defined(__R_Type__Vec3__) */
