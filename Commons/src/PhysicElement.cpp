//
// PhysicElement.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:30:06 2013 Samuel Olivier
//

#include <cmath>
#include "PhysicElement.h"
#include "Sprite.h"

PhysicElement::PhysicElement() : _rotation(0), _hasChanged(true) {

    _attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

PhysicElement::PhysicElement(PhysicElement const& other) :
_attributesMutex(), _pos(other._pos), _size(other._size),
_rotation(other._rotation), _hasChanged(true), _type(other._type) {
    _attributesMutex.resize(other._attributesMutex.size());
    for (uint32 i = 0; i < _attributesMutex.size(); ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

PhysicElement::~PhysicElement() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void	PhysicElement::setPosition(Vec2 const& pos) {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
}

void	PhysicElement::move(Vec2 const& move) {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	if (move != Vec2(0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
}

Vec2 const& PhysicElement::getPosition() const {
    Threading::MutexLocker  locker(_attributesMutex[ePosition]);
	return (_pos);
}

void	PhysicElement::setSize(Vec2 const& size) {
    Threading::MutexLocker locker(_attributesMutex[eSize]);
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
}

Vec2 const&	PhysicElement::getSize() const {
    Threading::MutexLocker  locker(_attributesMutex[eSize]);
	return (_size);
}

void	PhysicElement::setRotation(float32 rotation) {
    Threading::MutexLocker locker(_attributesMutex[eRotation]);
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
}

float32	PhysicElement::getRotation() const {
    Threading::MutexLocker  locker(_attributesMutex[eRotation]);
	return (_rotation);
}

bool	PhysicElement::hasChanged() const {
    Threading::MutexLocker  locker(_attributesMutex[eHasChanged]);
	return (_hasChanged);
}

void	PhysicElement::setChanged(bool changed) {
    Threading::MutexLocker  locker(_attributesMutex[eHasChanged]);
	_hasChanged = changed;
}

void	PhysicElement::setType(Type c) {
    Threading::MutexLocker  locker(_attributesMutex[eType]);
	_type = c;
}

IPhysicElement::Type	PhysicElement::getType() const {
    Threading::MutexLocker  locker(_attributesMutex[eType]);
	return ((Type)_type);
}

Network::APacket&		operator<<(Network::APacket& packet, PhysicElement& element) {
	packet << element.getId() << element.getPosition() << element.getRotation() << element.getSize();
	return (packet);
}

PhysicElement::Box::Box(float32 posX, float32 posY, float32 w, float32 h, float32 angle) :
  posX(posX), posY(posY), w(w), h(h), angle(angle), out(NULL) {
}

void PhysicElement::Box::rotate(Box& other) {
  float32 cosA = cos(-other.angle);
  float32 sinA = sin(-other.angle);
  float32 oXDif = posX - other.posX;
  float32 oYDif = posY - other.posY;
  float32 oXDif2 = oXDif * cosA - oYDif * sinA;
  float32 oYDif2 = oXDif * sinA + oYDif * cosA;
  posX = other.posX + oXDif2;
  posY = other.posY + oYDif2;
  angle -= other.angle;
  update();
}

void PhysicElement::Box::update() {
  float32 absCosA = std::abs(cos(angle));
  float32 absSinA = std::abs(sin(angle));
  float32 ow = w * absCosA + h *absSinA;
  float32 oh = w * absSinA + h *absCosA;
  float32 oX = posX;
  float32 oY = posY;
  out = new Box(ow, oh, oX, oY, 0);
}

bool PhysicElement::Box::simpleCollision(Box& box1, Box& box2)
{
  double offsetX1 = box1.posX - box1.w/2.;
  double offsetY1 = box1.posY - box1.h/2.;
  double offsetX2 = box2.posX - box2.w/2.;
  double offsetY2 = box2.posY - box2.h/2.;
    
  return !(offsetX1 > offsetX2 + box2.w
	   || offsetY1 > offsetY2 + box2.h
	   || offsetX2 > offsetX1 + box1.w
	   || offsetY2 > offsetY1 + box1.h);
}

bool PhysicElement::collision(PhysicElement& elem1, PhysicElement& elem2) {
  Box box1(elem1._pos.x, elem1._pos.y, elem1._size.x - 0.01, elem1._size.y - 0.01, elem1._rotation);
  Box box2(elem2._pos.x, elem2._pos.y, elem2._size.x - 0.01, elem2._size.y - 0.01, elem2._rotation);
    
    return Box::simpleCollision(box1, box2);

  box2.rotate(box1);

  if(!Box::simpleCollision(box1,*box2.out))
    return false;
  
  Box box3(elem2._pos.x, elem2._pos.y, elem2._size.x, elem2._size.y, elem2._rotation);
  box1.rotate(box3);
  if(!Box::simpleCollision(*box1.out,box3))
    return false;

  return true;
}
