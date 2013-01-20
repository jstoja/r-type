//
// Viewport.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 17 14:27:23 2013 Samuel Olivier
//

#include "Viewport.h"

Viewport::Viewport(float32 speed) : _x(0), _width(16), _speed(speed) {
    _attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

Viewport::~Viewport() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void	Viewport::setPosition(float32 x) {
    Threading::MutexLocker  locker(_attributesMutex[eX]);
	_x = x;
}

float32	Viewport::getPosition() const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
	return (_x);
}

void	Viewport::setWidth(float32 width) {
    Threading::MutexLocker  locker(_attributesMutex[eWidth]);
	_width = width;
}

float32	Viewport::getWidth() const {
    Threading::MutexLocker locker(_attributesMutex[eWidth]);
	return (_width);
}

void	Viewport::setSpeed(float32 speed) {
    Threading::MutexLocker  locker(_attributesMutex[eSpeed]);
	_speed = speed;
}

float32	Viewport::getSpeed() const {
    Threading::MutexLocker locker(_attributesMutex[eSpeed]);
	return (_speed);
}

bool	Viewport::isInViewport(float32 x) const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
    Threading::MutexLocker locker1(_attributesMutex[eWidth]);
    //Threading::MutexLocker locker2(_attributesMutex[eSpeed]);
	return (x >= _x && x < _x + _width);
}

bool	Viewport::isInViewport(Rect2 const& object) const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
    Threading::MutexLocker locker1(_attributesMutex[eWidth]);
	return ((object.pos.x >= _x && object.pos.x < _x + _width) ||
		(object.pos.x + object.size.x >= _x && object.pos.x + object.size.x < _x + _width) ||
		(object.pos.x < _x && object.pos.x + object.size.x >= _x + _width));
}

void	Viewport::update(Clock& clock) {
    Threading::MutexLocker locker(_attributesMutex[eX]);
    Threading::MutexLocker locker1(_attributesMutex[eSpeed]);
	_x += (float32)clock.getEllapsedTime() / 1000 * _speed;
}