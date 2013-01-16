//
//  Vec3.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Vec3.h"

#include "Vec2.h"

Vec3::Vec3(void) : x(0), y(0), z(0) {
}

Vec3::Vec3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {
}

Vec3::Vec3(uint32 color) : x(0), y(0), z(0) {
    uint8* composants = (uint8*)&color;
    x = (float32)composants[2] / 0xff;
    y = (float32)composants[1] / 0xff;
    z = (float32)composants[0] / 0xff;
}

Vec3::Vec3(Vec2 const& v, float32 z) : x(v.x), y(v.y), z(z) {    
}

bool Vec3::operator>=(Vec3 const& v3) const{
    return x >= v3.x && y >= v3.y && z >= v3.z;
}

bool Vec3::operator<=(Vec3 const& v3) const{
    return x <= v3.x && y <= v3.y && z <= v3.z;
}

Vec3 Vec3::operator+(Vec3 const& v3) const{
    return Vec3(x + v3.x, y + v3.y, z + v3.z);
}

Vec3 Vec3::operator-(Vec3 const& v3) const{
    return Vec3(x - v3.x, y - v3.y, z - v3.z);
}

Vec3 Vec3::operator/(Vec3 const& v3) const{
    return Vec3(x / v3.x, y / v3.y, z / v3.z);
}

Vec3 Vec3::operator*(Vec3 const& v3) const{
    return Vec3(x * v3.x, y * v3.y, z * v3.z);
}

Vec3 Vec3::operator/(float32 v) const{
    return Vec3(x / v, y / v, z / v);
}

Vec3 Vec3::operator*(float32 v) const{
    return Vec3(x * v, y * v, z * v);
}

std::ostream& operator<<(std::ostream& stream, Vec3 const& v) {
    return stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

bool    Vec3::operator==(Vec3 const& v) const {
    return (x == v.x && y == v.y && z == v.z);
}

bool    Vec3::operator!=(Vec3 const& v) const {
    return !(*this == v);
}