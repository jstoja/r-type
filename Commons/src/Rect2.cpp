//
//  Rect.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Rect2.h"

Rect2::Rect2(float32 x, float32 y, float32 width, float32 height)
: pos(x, y), size(width, height) {
}

Rect2::Rect2(Vec2 const& pos, Vec2 const& size)
: pos(pos), size(size) {
}

Rect2::~Rect2() {
}

bool Rect2::in(Vec2 const& point) const {
    return pos <= point && (pos + size) >= point;
}

std::ostream& operator<<(std::ostream& stream, Rect2 const& rect) {
    return stream << "(" << rect.pos.x << ", " << rect.pos.y
    << ", " << rect.size.x << ", " << rect.size.y << ")";
}