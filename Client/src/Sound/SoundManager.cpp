#include "SoundManager.h"
#include "ISound.h"
#include "SFMLSound.h"

Sound::SoundManager::SoundManager() {  
}

Sound::SoundManager::~SoundManager() {
}

void	Sound::SoundManager::load(std::string const& name) {
  SFMLSound	*snd = new SFMLSound(name);

  _soundsName[name] = snd;
  _soundsId[snd->getId()] = snd;
}

void	Sound::SoundManager::remove(std::string const& name) {
  ISound *item = getSound(name);

  if (item != NULL) {
      _soundsId.erase(item->getId());
      _soundsName.erase(item->getName());
  }
}

void	Sound::SoundManager::play(std::string const& name) {
  ISound *item = getSound(name);

  if (item != NULL) {
    item->play();
  }
}

void	Sound::SoundManager::play(uint32 id) {
  ISound *item = getSound(id);

  if (item != NULL) {
    item->play();
  }
}

Sound::ISound	*Sound::SoundManager::getSound(uint32 id) {
  std::map<uint32, ISound*>::const_iterator it;  

  if ((it = _soundsId.find(id)) != _soundsId.end())
    return it->second;
  return NULL;
}

Sound::ISound	*Sound::SoundManager::getSound(std::string const& name) {
  std::map<std::string, ISound*>::const_iterator it;  

  if ((it = _soundsName.find(name)) != _soundsName.end())
    return it->second;
  return NULL;
}
