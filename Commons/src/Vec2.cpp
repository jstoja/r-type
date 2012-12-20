//
//  Vec2.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Vec2.h"

Vec2::Vec2(float32 x, float32 y) : x(x), y(y) {
}

bool operator>=(Vec2 const& v1, Vec2 const& v2) {
    return v1.x >= v2.x && v1.y >= v2.y;
}

bool operator<=(Vec2 const& v1, Vec2 const& v2) {
    return v1.x <= v2.x && v1.y <= v2.y;
}

Vec2 operator+(Vec2 const& v1, Vec2 const& v2) {
    return Vec2(v1.x + v2.x, v1.y + v2.y);
}

std::ostream& operator<<(std::ostream& stream, Vec2 const& v) {
    return stream << "Vec2(" << v.x << ", " << v.y << ")";
}