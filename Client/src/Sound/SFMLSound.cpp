//
//  Sound.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//
# include <SFML/Audio.hpp>
# include <iostream>
# include <stdexcept>

#include "UUIDGenerator.h"
#include "Sound.h"

Sound::Sound::Sound(std::string const& name) {  
	try {
		_id = UUIDGenerator::getInstance().getUUID();
		_name = name;
		if (_buf.loadFromFile(name)) {
			_sound.setBuffer(_buf);
		}
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

void	Sound::Sound::load(std::string const& name) {
	try {
		if (_buf.loadFromFile(name)) {
			_sound.setBuffer(_buf);
		}
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
