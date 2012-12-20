//
//  Channel.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//
#include "Sound.h"
#include "Channel.h"

Sound::Channel::Channel(Sound* sound) {
	_sound = sound;
}

Sound::Channel::~Channel() {
}

void	Sound::Channel::setSound(Sound* sound) {
	_sound = sound;
}

void	Sound::Channel::play() {
	if (_sound)
		_sound->play();
}

void	Sound::Channel::stop() {
	if (_sound) {
		_sound->play();
	}
}

bool	Sound::Channel::isPlaying() const {
	if (_sound) {
		return _sound->isPlaying();
	}
	return false;
}

uint32	Sound::Channel::getId() const {
	if (_sound) {
		return _sound->getId();
	}
	return -1;
}

std::string const&	Sound::Channel::getName() const {
	return _sound->getName();
}

Sound::Sound*	Sound::Channel::getSound() const {
	return _sound;
}
