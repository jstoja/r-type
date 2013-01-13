//
// GraphicElement.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 16:56:43 2013 Samuel Olivier
//

#include "GraphicElement.h"
#include "Sprite.h"

GraphicElement::GraphicElement() : _rotation(0), _hasChanged(true) {
}

GraphicElement::~GraphicElement() {
}

void	GraphicElement::setPosition(Vec3 const& pos) {
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
}

void	GraphicElement::move(Vec3 const& move) {
	if (move != Vec3(0, 0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
}

Vec3 const& GraphicElement::getPosition() const {
	return (_pos);
}

void	GraphicElement::setSize(Vec2 const& size) {
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
}

Vec2 const&	GraphicElement::getSize() const {
	return (_size);
}

void	GraphicElement::setRotation(float32 rotation) {
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
}

float32	GraphicElement::getRotation() const {
	return (_rotation);
}

bool	GraphicElement::hasChanged() const {
	return (_hasChanged);
}

void	GraphicElement::setChanged(bool changed) {
	_hasChanged = changed;
}

void	GraphicElement::setSprite(ISprite *sprite) {
	_sprite = dynamic_cast<Sprite *>(sprite);
}

Sprite	*GraphicElement::getSprite() const {
	return (_sprite);
}

void	GraphicElement::setSpriteFrameIndex(char idx) {
	_spriteIndex = idx;
}

char	GraphicElement::getSpriteFrameIndex() const {
	return (_spriteIndex);
}

Network::APacket&		operator<<(Network::APacket& packet, GraphicElement& element) {
	element.setChanged(false);
	packet << element.getId() << element.getPosition() << element.getRotation() << element.getSize() << element.getSprite()->getId() << element.getSpriteFrameIndex();
	return (packet);
}
