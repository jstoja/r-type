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
}

Scenery::~Scenery() {
}

void		Scenery::setTexture(ITexture* texture) {
	_texture = dynamic_cast<Texture*>(texture);
}

Texture*	Scenery::getTexture() const {
	return (_texture);
}
	
void	Scenery::setSpeed(float32 speed) {
	_speed = speed;
}

float32	Scenery::getSpeed() const {
	return (_speed);
}

void	Scenery::setWidth(float32 width) {
	_width = width;
}

float32	Scenery::getWidth() const {
	return (_width);
}

void	Scenery::setXStart(float32 xStart) {
	_xStart = xStart;
}

float32	Scenery::getXStart() const {
	return (_xStart);
}

void	Scenery::setXEnd(float32 xEnd) {
	_xEnd = xEnd;
}

float32	Scenery::getXEnd() const {
	return (_xEnd);
}

Network::APacket&		operator<<(Network::APacket& packet, Scenery const& scenery) {
	return packet << scenery.getId() << scenery.getTexture()->getId() << scenery.getSpeed()
				  << scenery.getWidth() << scenery.getXStart() << scenery.getXEnd();
}
