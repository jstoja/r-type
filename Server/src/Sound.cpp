//
// Sound.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 01:12:55 2013 Samuel Olivier
//

#include <Application.h>
#include <ResourcesManager.h>

#include "Sound.h"

Sound::Sound(std::string const& filepath) : _changed(false), _isPlaying(false), _repeat(0) {
	_sound = ResourcesManager::getInstance().loadResource(filepath);
}

Sound::~Sound() {
	delete _sound;
}

Resource*	Sound::getSound() const {
	return (_sound);
}

void	Sound::setRepeat(int32 repeat) {
	_repeat = repeat;
}

int32	Sound::getRepeat() const {
	return (_repeat);
}

void	Sound::play() {
	_isPlaying = true;
	_changed = true;
}

void	Sound::stop() {
	_isPlaying = false;
	_changed = true;
}

bool	Sound::hasChanged() const {
	return (_changed);
}

void	Sound::setChanged(bool val) {
	_changed = val;
}

Network::APacket&		operator<<(Network::APacket& packet, Sound const& sound) {
	packet << sound.getId() << sound.getSound()->getId() << sound.getRepeat();
	return (packet);
}
