//
//  Element.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Element.h"

Graphic::Element::Element(void)
: Object(), _position(), _rotation(), _size(), _sprite(NULL) {
}

Graphic::Element::Element(uint32 id)
: Object(id), _position(), _rotation(), _size(), _sprite(NULL) {
}

Graphic::Element::~Element(void) {
}

Vec2 const&Graphic::Element::getPosition(void) const {
    return _position;
}

void Graphic::Element::setPosition(Vec2 const& position) {
    _position = position;
}

float32 Graphic::Element::getRotation(void) const {
    return _rotation;
}

void Graphic::Element::setRotation(float32 rotation) {
    _rotation = rotation;
}

Vec2 const& Graphic::Element::getSize(void) const {
    return _size;
}

void Graphic::Element::setSize(float32 size) {
    _size = size;
}

Graphic::Sprite* Graphic::Element::getSprite(void) const {
    return _sprite;
}

void Graphic::Element::setSprite(Sprite* sprite) {
    _sprite = sprite;
}