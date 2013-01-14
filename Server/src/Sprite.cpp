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

void	Sprite::addFrame(Vec2 const& p1, Vec2 const& p2) {
	_frames.push_back(Frame(p1, p2));
}

std::list<Frame> const&	Sprite::getFrames() const {
	return (_frames);
}

Network::APacket&		operator<<(Network::APacket& packet, Sprite const& sprite) {
	packet << sprite.getId() << sprite.getTexture()->getId() << sprite.getFrames();
	return packet;
}
