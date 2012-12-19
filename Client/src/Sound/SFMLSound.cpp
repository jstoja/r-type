#include "UUIDGenerator.h"
#include "ISound.h"
#include "SFMLSound.h"

Sound::SFMLSound::SFMLSound(std::string const& name) {  
  _id = Utilities::UUIDGenerator::getInstance().getUUID();
  _name = name;
  if (_buf.LoadFromFile(name))
    _sound.SetBuffer(_buf);
  else
    std::cerr << "load from file fail" << std::endl;
}

Sound::SFMLSound::~SFMLSound() {
}

void	Sound::SFMLSound::play() {
  _sound.Play();
}

void	Sound::SFMLSound::stop() {
  _sound.Stop();
}

void	Sound::SFMLSound::load(std::string const& name) {
  if (_buf.LoadFromFile(name))
    _sound.SetBuffer(_buf);
  else
    std::cerr << "load from file fail" << std::endl;
}

uint32	Sound::SFMLSound::getId() const {
  return _id;
}

std::string const&	Sound::SFMLSound::getName() const {
  return _name;
}

int	main() {
  // simple test for play a sound
  Sound::SFMLSound	sound("marseille.wav");
  sound.play();
  sleep(2);
  return (0);
}
