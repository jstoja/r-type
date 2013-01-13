//
// Sprite.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 17:51:22 2013 Samuel Olivier
//

#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite() {

}

Sprite::Sprite(ITexture *texture) {
	setTexture(texture);
}

Sprite::~Sprite() {

}

void	Sprite::setTexture(ITexture *texture) {
	_texture = dynamic_cast<Texture*>(texture);
}

Texture*	Sprite::getTexture() const {
	return (_texture);
}

void	Sprite::addFrame(Rect2 const& frame) {
	_frames.push_back(frame);
}

std::list<Rect2> const&	Sprite::getFrames() const {
	return (_frames);
}

Network::TcpPacket&		operator<<(Network::TcpPacket& packet, Sprite const& sprite) {
	packet << sprite.getId() << sprite.getTexture()->getId() << sprite.getFrames();
	return packet;
}
