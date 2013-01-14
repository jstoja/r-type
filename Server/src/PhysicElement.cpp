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
}

PhysicElement::~PhysicElement() {
}

void	PhysicElement::setPosition(Vec2 const& pos) {
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
}

void	PhysicElement::move(Vec2 const& move) {
	if (move != Vec2(0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
}

Vec2 const& PhysicElement::getPosition() const {
	return (_pos);
}

void	PhysicElement::setSize(Vec2 const& size) {
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
}

Vec2 const&	PhysicElement::getSize() const {
	return (_size);
}

void	PhysicElement::setRotation(float32 rotation) {
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
}

float32	PhysicElement::getRotation() const {
	return (_rotation);
}

bool	PhysicElement::hasChanged() const {
	return (_hasChanged);
}

void	PhysicElement::setChanged(bool changed) {
	_hasChanged = changed;
}

void	PhysicElement::setType(Type c) {
	_type = c;
}

IPhysicElement::Type	PhysicElement::getType() const {
	return ((Type)_type);
}

Network::APacket&		operator<<(Network::APacket& packet, PhysicElement& element) {
	element.setChanged(false);
	packet << element.getId() << element.getPosition() << element.getRotation() << element.getSize();
	return (packet);
}
