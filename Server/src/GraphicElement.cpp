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
    _attributesMutex[ePosition]->lock();
	if (pos != _pos) {
		_pos = pos;
		setChanged(true);
	}
    _attributesMutex[ePosition]->unlock();
}

void	GraphicElement::move(Vec3 const& move) {
    _attributesMutex[ePosition]->lock();
	if (move != Vec3(0, 0, 0)) {
		_pos = _pos + move;
		setChanged(true);
	}
    _attributesMutex[ePosition]->unlock();
}

Vec3 const& GraphicElement::getPosition() const {
    Threading::MutexLocker locker(_attributesMutex[ePosition]);
	return (_pos);
}

void	GraphicElement::setSize(Vec2 const& size) {
    _attributesMutex[eSize]->lock();
	if (size != _size) {
		_size = size;
		setChanged(true);
	}
    _attributesMutex[eSize]->unlock();
}

Vec2 const&	GraphicElement::getSize() const {
    Threading::MutexLocker locker(_attributesMutex[eSize]);
	return (_size);
}

void	GraphicElement::setRotation(float32 rotation) {
    _attributesMutex[eRotation]->lock();
	if (_rotation != rotation) {
		_rotation = rotation;
		setChanged(true);
	}
    _attributesMutex[eRotation]->unlock();
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
    _attributesMutex[eHasChanged]->lock();
	_hasChanged = changed;
    _attributesMutex[eHasChanged]->unlock();
}

void	GraphicElement::setSprite(ISprite *sprite) {
    _attributesMutex[eSprite]->lock();
	_sprite = dynamic_cast<Sprite *>(sprite);
    _attributesMutex[eSprite]->unlock();
}

Sprite	*GraphicElement::getSprite() const {
    Threading::MutexLocker locker(_attributesMutex[eSprite]);
	return (_sprite);
}

void	GraphicElement::setSpriteFrameIndex(char idx) {
    _attributesMutex[eSpriteIndex]->lock();
	_spriteIndex = idx;
    _attributesMutex[eSpriteIndex]->unlock();
}

char	GraphicElement::getSpriteFrameIndex() const {
    Threading::MutexLocker locker(_attributesMutex[eSpriteIndex]);
	return (_spriteIndex);
}

void	GraphicElement::setType(Type c) {
    _attributesMutex[eType]->lock();
	_type = c;
    _attributesMutex[eType]->unlock();
}

IGraphicElement::Type	GraphicElement::getType() const {
    Threading::MutexLocker locker(_attributesMutex[eType]);
	return ((Type)_type);
}

Rect2            GraphicElement::getRect(void) const {
    return Rect2(Vec2(_pos) - _size / 2, _size);
}

Network::APacket&		operator<<(Network::APacket& packet, GraphicElement& element) {
	element.setChanged(false);
	packet << element.getId() << element.getPosition() << element.getRotation()
		   << element.getSize() << element.getSprite()->getId() << element.getSpriteFrameIndex()
		   << (char)element.getType();
	return (packet);
}
