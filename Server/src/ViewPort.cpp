//
// Viewport.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 17 14:27:23 2013 Samuel Olivier
//

#include "ViewPort.h"

ViewPort::ViewPort(float32 speed) : _x(0), _width(16), _speed(speed) {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

ViewPort::~ViewPort() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void	ViewPort::setPosition(float32 x) {
    _attributesMutex[eX]->lock();
	_x = x;
    _attributesMutex[eX]->unlock();
}

float32	ViewPort::getPosition() const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
	return (_x);
}

void	ViewPort::setWidth(float32 width) {
    _attributesMutex[eWidth]->lock();
	_width = width;
    _attributesMutex[eWidth]->unlock();
}

float32	ViewPort::getWidth() const {
    Threading::MutexLocker locker(_attributesMutex[eWidth]);
	return (_width);
}

void	ViewPort::setSpeed(float32 speed) {
    _attributesMutex[eSpeed]->lock();
	_speed = speed;
    _attributesMutex[eSpeed]->unlock();
}

float32	ViewPort::getSpeed() const {
    Threading::MutexLocker locker(_attributesMutex[eSpeed]);
	return (_speed);
}

bool	ViewPort::isInViewport(float32 x) const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
    Threading::MutexLocker locker1(_attributesMutex[eWidth]);
    Threading::MutexLocker locker2(_attributesMutex[eSpeed]);
	return (x >= _x && x < _x + _width);
}

bool	ViewPort::isInViewport(Rect2 const& object) const {
    Threading::MutexLocker locker(_attributesMutex[eX]);
    Threading::MutexLocker locker1(_attributesMutex[eWidth]);
    Threading::MutexLocker locker2(_attributesMutex[eSpeed]);
	return ((object.pos.x >= _x && object.pos.x < _x + _width) ||
		(object.pos.x + object.size.x >= _x && object.pos.x + object.size.x < _x + _width) ||
		(object.pos.x < _x && object.pos.x + object.size.x >= _x + _width));
}

void	ViewPort::update(Clock& clock) {
    _attributesMutex[eX]->lock();
    _attributesMutex[eSpeed]->lock();
	_x += clock.getEllapsedTime() * _speed;
    _attributesMutex[eX]->unlock();
    _attributesMutex[eSpeed]->unlock();
}