#include "SoundManager.h"
#include "Sound.h"

Sound::SoundManager::SoundManager() {  
}

Sound::SoundManager::~SoundManager() {
}

void	Sound::SoundManager::load(std::string const& name) {
  Sound		*snd = new Sound(name);

  _soundsName[name] = snd;
  _soundsId[snd->getId()] = snd;
}

void	Sound::SoundManager::remove(std::string const& name) {
  Sound *item = getSound(name);

  if (item != NULL) {
      _soundsId.erase(item->getId());
      _soundsName.erase(item->getName());
  }
}

void	Sound::SoundManager::play(std::string const& name) {
  Sound *item = getSound(name);

  if (item != NULL) {
    item->play();
  }
}

void	Sound::SoundManager::play(uint32 id) {
  Sound *item = getSound(id);

  if (item != NULL) {
    item->play();
  }
}

Sound::Sound	*Sound::SoundManager::getSound(uint32 id) {
  std::map<uint32, Sound*>::const_iterator it;  

  if ((it = _soundsId.find(id)) != _soundsId.end())
    return it->second;
  return NULL;
}

Sound::Sound	*Sound::SoundManager::getSound(std::string const& name) {
  std::map<std::string, Sound*>::const_iterator it;  

  if ((it = _soundsName.find(name)) != _soundsName.end())
    return it->second;
  return NULL;
}

bool	Sound::SoundManager::isPlaying(uint32 id) {
  Sound	*snd = getSound(id);

  if (snd) {
    return snd->isPlaying();
  }
  return false;
}

bool	Sound::SoundManager::isPlaying(std::string const& name) {
  Sound	*snd = getSound(name);

  if (snd) {
    return snd->isPlaying();
  }
  return false;
}

int	main() {
  Sound::SoundManager	manager;

  manager.load("marseille.wav");
  //  manager.load("highpass.wav");
  manager.play("marseille.wav");
  //  manager.play("highpass.wav");
  sleep(2);
  // manager.load("marseille.wav");
  // manager.play("marseille.wav");
  // sleep(2);
  // Sound::Sound *snd = manager.getSound("marseille.wav");
  // snd->play();
  // sleep(2);
  // manager.remove("marseille.wav");
  // Sound::I Sound *snd2 = manager.getSound("marseille.wav");
  // if (snd2 == NULL)
  //   std::cerr << "succes" << std::endl;
  return (0);
}
