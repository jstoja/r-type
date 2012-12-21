//
//  Element.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Element.h"

#include "Debug.h"

Graphic::Element::Element(void) :
Object(), _position(), _rotation(0), _size(), _sprite(NULL),
_updateTransformationMatrix(true) {
}

Graphic::Element::Element(uint32 id) :
Object(id), _position(), _rotation(0), _size(), _sprite(NULL),
_updateTransformationMatrix(true) {
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

void Graphic::Element::setSize(Vec2 const& size) {
    _size = size;
}

Graphic::Sprite* Graphic::Element::getSprite(void) const {
    return _sprite;
}

void Graphic::Element::setSprite(Sprite* sprite) {
    _sprite = sprite;
}

Graphic::Matrix4f const& Graphic::Element::getTransformationMatrix(void) {
    if (_updateTransformationMatrix)
        _updateTransformationMatrix = false;
    _transformationMatrix.identity();
    _transformationMatrix.translate(_position.x, _position.y);
    if (_size.x != 0 || _size.y != 0)
        _transformationMatrix.scale(_size.x, _size.y);
    if (_rotation != 0)
        _transformationMatrix.rotate(_rotation);
    return _transformationMatrix;
}

Rect Graphic::Element::getRect() const {
    return Rect(_position - _size / 2, _size);
}