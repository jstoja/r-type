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
    _attributesMutexFrames = new Threading::Mutex();
    _attributesMutexTexture = new Threading::Mutex();
}

Sprite::Sprite(ITexture *texture) {
    _attributesMutexFrames = new Threading::Mutex();
    _attributesMutexTexture = new Threading::Mutex();
	setTexture(texture);
}

Sprite::~Sprite() {
    delete _attributesMutexFrames;
    delete _attributesMutexTexture;
}

void	Sprite::setTexture(ITexture *texture) {
    _attributesMutexTexture->lock();
	_texture = dynamic_cast<Texture*>(texture);
    _attributesMutexTexture->unlock();
}

Texture*	Sprite::getTexture() const {
    Threading::MutexLocker locker(_attributesMutexTexture);
	return (_texture);
}

void	Sprite::addFrame(Vec2 const& p1, Vec2 const& p2) {
    _attributesMutexFrames->lock();
	_frames.push_back(Frame(p1, p2));
    _attributesMutexFrames->unlock();
}

std::list<Frame> const&	Sprite::getFrames() const {
    Threading::MutexLocker locker(_attributesMutexFrames);
	return (_frames);
}

Network::APacket&		operator<<(Network::APacket& packet, Sprite const& sprite) {
	packet << sprite.getId() << sprite.getTexture()->getId() << sprite.getFrames();
	return packet;
}
