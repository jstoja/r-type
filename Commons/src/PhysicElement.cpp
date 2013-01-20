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
	element.setChanged(false);
	packet << element.getId() << element.getPosition() << element.getRotation() << element.getSize();
	return (packet);
}

PhysicElement::Box::Box(float32 posX, float32 posY, float32 w, float32 h, float32 angle) :
  posX(posX), posY(posY), w(w), h(h), angle(angle) {
}

void PhysicElement::Box::rotate(Box& other) {
  double cosA = cos(-other.angle * 0.0174532925);
  double sinA = sin(-other.angle * 0.0174532925);
  double oXDif = posX - other.posX;
  double oYDif = posY - other.posY;
  double oXDif2 = oXDif * cosA - oYDif * sinA;
  double oYDif2 = oXDif * sinA + oYDif * cosA;
  posX = other.posX + oXDif2;
  posY = other.posY + oYDif2;
  angle -= other.angle;
  //UpdateOutLineRect_private();
}

void PhysicElement::Box::update() {
  
}

bool PhysicElement::collision(PhysicElement& elem1, PhysicElement& elem2) {
  Box box1(elem1._pos.x, elem1._pos.y, elem1._size.x, elem1._size.y, elem1._rotation);
  Box box2(elem2._pos.x, elem2._pos.y, elem2._size.x, elem2._size.y, elem2._rotation);

  
  return false;
}
