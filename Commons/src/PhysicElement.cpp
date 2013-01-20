//
// PhysicElement.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:30:06 2013 Samuel Olivier
//

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

bool PhysicElement::collision(PhysicElement& elem1, PhysicElement& elem2) {
  
  return false;
}
