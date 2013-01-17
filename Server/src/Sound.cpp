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
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
	_sound = ResourcesManager::getInstance().loadResource(filepath, true);
}

Sound::~Sound() {
	delete _sound;
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

Resource*	Sound::getSound() const {
    Threading::MutexLocker locker(_attributesMutex[eSound]);
	return (_sound);
}

void	Sound::setRepeat(int32 repeat) {
	_repeat = repeat;
}

int32	Sound::getRepeat() const {
    Threading::MutexLocker locker(_attributesMutex[eRepeat]);
	return (_repeat);
}

void	Sound::play() {
    _attributesMutex[eIsPlaying]->lock();
    _attributesMutex[eChanged]->lock();
	_isPlaying = true;
	_changed = true;
    _attributesMutex[eIsPlaying]->unlock();
    _attributesMutex[eChanged]->unlock();
}

void	Sound::stop() {
    _attributesMutex[eIsPlaying]->lock();
    _attributesMutex[eChanged]->lock();
	_isPlaying = false;
	_changed = true;
    _attributesMutex[eIsPlaying]->unlock();
    _attributesMutex[eChanged]->unlock();
}

bool    Sound::isPlaying() const {
    Threading::MutexLocker locker(_attributesMutex[eIsPlaying]);
    return _isPlaying;
}

bool	Sound::hasChanged() const {
    Threading::MutexLocker locker(_attributesMutex[eChanged]);
	return (_changed);
}

void	Sound::setChanged(bool val) {
    _attributesMutex[eChanged]->lock();
	_changed = val;
    _attributesMutex[eChanged]->unlock();
}

Network::APacket&		operator<<(Network::APacket& packet, Sound const& sound) {
	packet << sound.getId() << sound.getSound()->getId() << sound.getRepeat();
	return (packet);
}
