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
    _attributesMutex[ePosition]->lock();
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
    _attributesMutex[ePosition]->unlock();
}

void	PhysicElement::move(Vec2 const& move) {
    _attributesMutex[ePosition]->lock();
	if (move != Vec2(0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
    _attributesMutex[ePosition]->unlock();
}

Vec2 const& PhysicElement::getPosition() const {
    Threading::MutexLocker  locker(_attributesMutex[ePosition]);
	return (_pos);
}

void	PhysicElement::setSize(Vec2 const& size) {
    _attributesMutex[eSize]->lock();
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
    _attributesMutex[eSize]->unlock();
}

Vec2 const&	PhysicElement::getSize() const {
    Threading::MutexLocker  locker(_attributesMutex[eSize]);
	return (_size);
}

void	PhysicElement::setRotation(float32 rotation) {
    _attributesMutex[eRotation]->lock();
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
    _attributesMutex[eRotation]->unlock();
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
    _attributesMutex[eHasChanged]->lock();
	_hasChanged = changed;
    _attributesMutex[eHasChanged]->unlock();
}

void	PhysicElement::setType(Type c) {
    _attributesMutex[eType]->lock();
	_type = c;
    _attributesMutex[eType]->unlock();
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
