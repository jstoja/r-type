//
// Viewport.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 17 14:27:23 2013 Samuel Olivier
//

#include "ViewPort.h"

ViewPort::ViewPort(float32 speed) : _speed(speed), _width(16), _x(0) {
}

ViewPort::~ViewPort() {
}

void	ViewPort::setPosition(float32 x) {
	_x = x;
}

float32	ViewPort::getPosition() const {
	return (_x);
}

void	ViewPort::setWidth(float32 width) {
	_width = width;
}

float32	ViewPort::getWidth() const {
	return (_width);
}

void	ViewPort::setSpeed(float32 speed) {
	_speed = speed;
}

float32	ViewPort::getSpeed() const {
	return (_speed);
}

bool	ViewPort::isInViewport(float32 x) const {
	return (x >= _x && x < _x + _width);
}

bool	ViewPort::isInViewport(Rect2 const& object) const {
	return ((object.pos.x >= _x && object.pos.x < _x + _width) ||
		(object.pos.x + object.size.x >= _x && object.pos.x + object.size.x < _x + _width) ||
		(object.pos.x < _x && object.pos.x + object.size.x >= _x + _width));
}

void	ViewPort::update(Clock& clock) {
	_x += clock.getEllapsedTime() * _speed;
}