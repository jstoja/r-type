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

    _attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

GraphicElement::~GraphicElement() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void	GraphicElement::setPosition(Vec3 const& pos) {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
}

void	GraphicElement::move(Vec3 const& move) {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	if (move != Vec3(0, 0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
}

Vec3 const& GraphicElement::getPosition() const {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	return (_pos);
}

void	GraphicElement::setSize(Vec2 const& size) {
    Threading::MutexLocker locker(_attributesMutex[eSize]);
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
}

Vec2 const&	GraphicElement::getSize() const {
    Threading::MutexLocker locker(_attributesMutex[eSize]);
	return (_size);
}

void	GraphicElement::setRotation(float32 rotation) {
    Threading::MutexLocker locker(_attributesMutex[eRotation]);
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
}

float32	GraphicElement::getRotation() const {
    Threading::MutexLocker locker(_attributesMutex[eRotation]);
	return (_rotation);
}

bool	GraphicElement::hasChanged() const {
    Threading::MutexLocker locker(_attributesMutex[eHasChanged]);
	return (_hasChanged);
}

void	GraphicElement::setChanged(bool changed) {
    Threading::MutexLocker locker(_attributesMutex[eHasChanged]);
	_hasChanged = changed;
}

void	GraphicElement::setSprite(ISprite *sprite) {
    Threading::MutexLocker locker(_attributesMutex[eSprite]);
	_sprite = dynamic_cast<Sprite *>(sprite);
}

Sprite	*GraphicElement::getSprite() const {
    Threading::MutexLocker locker(_attributesMutex[eSprite]);
	return (_sprite);
}

void	GraphicElement::setSpriteFrameIndex(char idx) {
    Threading::MutexLocker locker(_attributesMutex[eSpriteIndex]);
	_spriteIndex = idx;
}

uint8	GraphicElement::getSpriteFrameIndex() const {
    Threading::MutexLocker locker(_attributesMutex[eSpriteIndex]);
	return (_spriteIndex);
}

void	GraphicElement::setType(Type c) {
    Threading::MutexLocker locker(_attributesMutex[eType]);
	_type = c;
}

IGraphicElement::Type	GraphicElement::getType() const {
    Threading::MutexLocker locker(_attributesMutex[eType]);
	return ((Type)_type);
}

Rect2            GraphicElement::getRect(void) const {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
    Threading::MutexLocker locker1(_attributesMutex[eSize]);
    return Rect2(Vec2(_pos) - _size / 2, _size);
}

Network::APacket&		operator<<(Network::APacket& packet, GraphicElement& element) {
	element.setChanged(false);
	packet << element.getId() << element.getPosition() << element.getRotation()
		   << element.getSize() << element.getSprite()->getId() << element.getSpriteFrameIndex()
		   << (uint8)element.getType();
	return (packet);
}
