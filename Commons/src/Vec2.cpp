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

bool Vec2::operator>=(Vec2 const& v2) const{
    return x >= v2.x && y >= v2.y;
}

bool Vec2::operator<=(Vec2 const& v2) const{
    return x <= v2.x && y <= v2.y;
}

Vec2 Vec2::operator+(Vec2 const& v2) const{
    return Vec2(x + v2.x, y + v2.y);
}

Vec2 Vec2::operator-(Vec2 const& v2) const{
    return Vec2(x - v2.x, y - v2.y);
}

Vec2 Vec2::operator/(Vec2 const& v2) const{
    return Vec2(x / v2.x, y / v2.y);
}

Vec2 Vec2::operator*(Vec2 const& v2) const{
    return Vec2(x * v2.x, y * v2.y);
}

Vec2 Vec2::operator/(float32 v) const{
    return Vec2(x / v, y / v);
}

Vec2 Vec2::operator*(float32 v) const{
    return Vec2(x * v, y * v);
}

std::ostream& operator<<(std::ostream& stream, Vec2 const& v) {
    return stream << "(" << v.x << ", " << v.y << ")";
}

bool    Vec2::operator==(Vec2 const& v) const {
    return (x == v.x && y == v.y);
}

bool    Vec2::operator!=(Vec2 const& v) const {
    return !(*this == v);
}