//
//  Sound.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//

#include "Sound.h"

#ifdef AUDIO_SFML

# include <iostream>
# include <stdexcept>

# include "ByteArray.h"
# include "UUIDGenerator.h"
# include "Resource.h"

Sound::Sound::Sound(Resource *resource) {
	try {
		_id = UUIDGenerator::getInstance().getUUID();
		_name = resource->getName();
        ByteArray arr = resource->getData();
        char const *buffer = arr.getData();
		if (_buf.loadFromMemory(buffer, arr.getSize())) {
			_sound.setBuffer(_buf);
		}
        delete buffer;
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

Sound::Sound::~Sound() {
}

void	Sound::Sound::play() {
	_sound.play();
}

void	Sound::Sound::stop() {
	_sound.stop();
}

void	Sound::Sound::load(Resource *resource) {
    try {
		_name = resource->getName();
        ByteArray arr = resource->getData();
        char const *buffer = arr.getData();
		if (_buf.loadFromMemory(buffer, arr.getSize())) {
			_sound.setBuffer(_buf);
		}
        delete buffer;
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
}

uint32	Sound::Sound::getId() const {
	return _id;
}

std::string const&	Sound::Sound::getName() const {
	return _name;
}

bool	Sound::Sound::isPlaying() const {
	sf::Sound::Status st = _sound.getStatus();

	if (st == sf::Sound::Paused || st == sf::Sound::Stopped) {
		return false;
	}
	return true;
}

bool	Sound::Sound::operator==(Sound const& sound) {
	if (sound.getId() == _id) {
		return true;
	}
	return false;
}

# endif