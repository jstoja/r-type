//
//  Vec3.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Vec3.h"

Vec3::Vec3(float32 x, float32 y, float32 z) : x(x), y(y), z(z) {
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