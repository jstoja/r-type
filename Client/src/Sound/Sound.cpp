
# include <SFML/Audio.hpp>

#include "Utilities/UUIDGenerator.h"
#include "Sound.h"

Sound::Sound::Sound(std::string const& name) {  
  _id = Utilities::UUIDGenerator::getInstance().getUUID();
  _name = name;
  if (_buf.loadFromFile(name))
    _sound.setBuffer(_buf);
  else
    std::cerr << "load fail" << std::endl;
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
  if (_buf.loadFromFile(name))
    _sound.setBuffer(_buf);
  else
    std::cerr << "load fail" << std::endl;
}

uint32	Sound::Sound::getId() const {
  return _id;
}

std::string const&	Sound::Sound::getName() const {
  return _name;
}

bool	Sound::Sound::isPlaying() const {
  sf::Sound::Status st = _sound.getStatus();
  
  if (st == sf::Sound::Paused || st == sf::Sound::Stopped)
    return false;
  return true;
}

bool	Sound::Sound::operator==(Sound const& sound) {
  if (sound.getId() == _id)
    return true;
  return false;
}
