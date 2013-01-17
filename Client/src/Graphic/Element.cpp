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
Object(false),
_type(Dynamic), _position(), _rotation(0), _opacity(1), _size(),
_sprite(NULL), _currentFrame(0),
_updateTransformationMatrix(true), _isVisible(true) {
}

Graphic::Element::Element(uint32 id) :
Object(id), _position(), _rotation(0), _opacity(1), _size(),
_sprite(NULL), _currentFrame(0),
_updateTransformationMatrix(true), _isVisible(true) {
}

Graphic::Element::~Element(void) {
}

Graphic::Element::Type Graphic::Element::getType(void) const {
    return _type;
}

void Graphic::Element::setType(Graphic::Element::Type type) {
    _type = type;
}

Vec3 const&Graphic::Element::getPosition(void) const {
    return _position;
}

void Graphic::Element::setPosition(Vec3 const& position) {
    _position = position;
}

float32 Graphic::Element::getRotation(void) const {
    return _rotation;
}

void Graphic::Element::setRotation(float32 rotation) {
    _rotation = rotation;
}

void Graphic::Element::setOpacity(float32 opacity) {
    _opacity = opacity;
}

float32 Graphic::Element::getOpacity(void) {
    return _opacity;
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

uint16 Graphic::Element::getCurrentFrame(void) const {
    return _currentFrame;
}

void Graphic::Element::setCurrentFrame(uint16 frame) {
    _currentFrame = frame;
}

Graphic::Matrix4f const& Graphic::Element::getTransformationMatrix(void) {
    if (_updateTransformationMatrix)
        _updateTransformationMatrix = false;
    _transformationMatrix.identity();
    _transformationMatrix.translate(_position.x, _position.y, _position.z);
    if (_size.x != 0 || _size.y != 0)
        _transformationMatrix.scale(_size.x, _size.y);
    if (_rotation != 0)
        _transformationMatrix.rotate(_rotation);
    return _transformationMatrix;
}

Rect2 Graphic::Element::getRect() const {
    return Rect2(Vec2(_position) - _size / 2, _size);
}

void Graphic::Element::setVisible(bool visible) {
	_isVisible = visible;
}

bool Graphic::Element::isVisible(void) const {
	return (_isVisible);
}
