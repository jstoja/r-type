//
//  Element.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Element.h"

#include "Debug.h"
#include "Threading/MutexLocker.h"

Graphic::Element::Element(void) :
Object(false),
_type(Dynamic), _position(), _rotation(0.2), _opacity(1), _size(),
_sprite(NULL), _currentFrame(0),
_updateTransformationMatrix(true), _isVisible(true), _mutex(new Threading::Mutex()) {
}

Graphic::Element::Element(uint32 id) :
Object(id), _position(), _rotation(0), _opacity(1), _size(),
_sprite(NULL), _currentFrame(0),
_updateTransformationMatrix(true), _isVisible(true), _mutex(new Threading::Mutex()) {
}

Graphic::Element::~Element(void) {
    delete _mutex;
}

Graphic::Element::Type Graphic::Element::getType(void) const {
    Threading::MutexLocker lock(_mutex);
    return _type;
}

void Graphic::Element::setType(Graphic::Element::Type type) {
    Threading::MutexLocker lock(_mutex);
    _type = type;
}

Vec3 const&Graphic::Element::getPosition(void) const {
    Threading::MutexLocker lock(_mutex);
    return _position;
}

void Graphic::Element::setPosition(Vec3 const& position) {
    Threading::MutexLocker lock(_mutex);
    _position = position;
}

float32 Graphic::Element::getRotation(void) const {
    Threading::MutexLocker lock(_mutex);
    return _rotation;
}

void Graphic::Element::setRotation(float32 rotation) {
    Threading::MutexLocker lock(_mutex);
    _rotation = rotation;
}

void Graphic::Element::setOpacity(float32 opacity) {
    Threading::MutexLocker lock(_mutex);
    _opacity = opacity;
}

float32 Graphic::Element::getOpacity(void) {
    Threading::MutexLocker lock(_mutex);
    return _opacity;
}

Vec2 const& Graphic::Element::getSize(void) const {
    Threading::MutexLocker lock(_mutex);
    return _size;
}

void Graphic::Element::setSize(Vec2 const& size) {
    Threading::MutexLocker lock(_mutex);
    _size = size;
}

Graphic::Sprite* Graphic::Element::getSprite(void) const {
    Threading::MutexLocker lock(_mutex);
    return _sprite;
}

void Graphic::Element::setSprite(Sprite* sprite) {
    Threading::MutexLocker lock(_mutex);
    _sprite = sprite;
}

uint16 Graphic::Element::getCurrentFrame(void) const {
    Threading::MutexLocker lock(_mutex);
    return _currentFrame;
}

void Graphic::Element::setCurrentFrame(uint16 frame) {
    Threading::MutexLocker lock(_mutex);
    _currentFrame = frame;
}

Graphic::Matrix4f const& Graphic::Element::getTransformationMatrix(void) {
    Threading::MutexLocker lock(_mutex);
    if (_updateTransformationMatrix)
        _updateTransformationMatrix = false;
    _transformationMatrix.identity();
    _transformationMatrix.translate(_position.x, _position.y, _position.z);
    if (_size.x != 0 || _size.y != 0)
        _transformationMatrix.scale(_size.x, _size.y);
    return _transformationMatrix;
}

Rect2 Graphic::Element::getRect() const {
    Threading::MutexLocker lock(_mutex);
    return Rect2(Vec2(_position) - _size / 2, _size);
}

void Graphic::Element::setVisible(bool visible) {
    Threading::MutexLocker lock(_mutex);
	_isVisible = visible;
}

bool Graphic::Element::isVisible(void) const {
    Threading::MutexLocker lock(_mutex);
	return (_isVisible);
}
