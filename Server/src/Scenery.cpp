//
// Scenery.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 14:50:52 2013 Samuel Olivier
//

#include "Scenery.h"

Scenery::Scenery() : _texture(NULL), _speed(1), _width(0), _xStart(0), _xEnd(0) {
	_attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

Scenery::~Scenery() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void		Scenery::setTexture(ITexture* texture) {
    _attributesMutex[eTexture]->lock();
	_texture = dynamic_cast<Texture*>(texture);
    _attributesMutex[eTexture]->unlock();
}

Texture*	Scenery::getTexture() const {
    Threading::MutexLocker  locker(_attributesMutex[eTexture]);
	return (_texture);
}
	
void	Scenery::setSpeed(float32 speed) {
    _attributesMutex[eSpeed]->lock();
	_speed = speed;
    _attributesMutex[eSpeed]->unlock();
}

float32	Scenery::getSpeed() const {
    Threading::MutexLocker  locker(_attributesMutex[eSpeed]);
	return (_speed);
}

void	Scenery::setWidth(float32 width) {
    _attributesMutex[eWidth]->lock();
	_width = width;
    _attributesMutex[eWidth]->unlock();
}

float32	Scenery::getWidth() const {
    Threading::MutexLocker  locker(_attributesMutex[eWidth]);
	return (_width);
}

void	Scenery::setXStart(float32 xStart) {
    _attributesMutex[eXStart]->lock();
	_xStart = xStart;
    _attributesMutex[eXStart]->unlock();
}

float32	Scenery::getXStart() const {
    Threading::MutexLocker  locker(_attributesMutex[eXStart]);
	return (_xStart);
}

void	Scenery::setXEnd(float32 xEnd) {
    _attributesMutex[eXEnd]->lock();
	_xEnd = xEnd;
    _attributesMutex[eXEnd]->unlock();
}

float32	Scenery::getXEnd() const {
    Threading::MutexLocker  locker(_attributesMutex[eXEnd]);
	return (_xEnd);
}

void	Scenery::setDepth(float32 depth) {
    _attributesMutex[eDepth]->lock();
	_depth = depth;
    _attributesMutex[eDepth]->unlock();
}

float32	Scenery::getDepth() const {
    Threading::MutexLocker  locker(_attributesMutex[eDepth]);
	return (_depth);
}

void	Scenery::setOpacity(float32 opacity) {
    _attributesMutex[eOpacity]->lock();
	_opacity = opacity;
    _attributesMutex[eOpacity]->unlock();
}

float32	Scenery::getOpacity() const {
    Threading::MutexLocker  locker(_attributesMutex[eOpacity]);
	return (_opacity);
}


Network::APacket&		operator<<(Network::APacket& packet, Scenery const& scenery) {
	return (packet << scenery.getId() << scenery.getTexture()->getId() << scenery.getSpeed()
				  << scenery.getWidth() << scenery.getXStart() << scenery.getXEnd()
                  << scenery.getDepth() << scenery.getOpacity());
}
