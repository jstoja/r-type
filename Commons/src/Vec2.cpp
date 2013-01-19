//
//  Vec2.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Vec2.h"

#include <cmath>

Vec2::Vec2(float32 x, float32 y) : x(x), y(y) {
}

Vec2::Vec2(Vec3 const& v) : x(v.x), y(v.y) {
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

bool    Vec2::operator==(Vec2 const& v) const {
    return (x == v.x && y == v.y);
}

bool    Vec2::operator!=(Vec2 const& v) const {
    return !(*this == v);
}

float32 Vec2::norm(void) const {
    return (sqrt(x * x + y * y));
}

void    Vec2::normalize(void) {
    float32 n = norm();
    x /= n;
    y /= n;
}

std::ostream& operator<<(std::ostream& stream, Vec2 const& v) {
    return stream << "(" << v.x << ", " << v.y << ")";
}