#include <algorithm>
#include "Sound.h"
#include "Channel.h"
#include "ChannelGroup.h"

Sound::ChannelGroup::ChannelGroup() {
}

Sound::ChannelGroup::~ChannelGroup() {
}

bool	Sound::ChannelGroup::load(Sound* sound) {
  if (_channels.size() != 4) {
    _channels.push_back(new Channel(sound));
    return true;
  }
  return false;
} 

bool	Sound::ChannelGroup::play(uint32 id) {
  Sound	*sound = getSound(id);

  if (sound) {
    sound->play();
    return true;
  }
  return false;
}

bool	Sound::ChannelGroup::play(std::string const& name) {
  Sound	*sound = getSound(name);

  if (sound) {    
    sound->play();
    return true;
  }
  return false;
}

bool	Sound::ChannelGroup::stop(std::string const& name) {
  Sound	*sound = getSound(name);

  if (sound) {
    sound->stop();
    return true;
  }
  return false;
}

bool	Sound::ChannelGroup::stop(uint32 id) {
  Sound	*sound = getSound(id);

  if (sound) {
    sound->stop();
    return true;
  }
  return false;
}

bool	Sound::ChannelGroup::remove(std::string const& name) {
  Sound	*sound = getSound(name);

  if (sound)
    {
      std::vector<Channel*>::iterator it;

      for (it = _channels.begin(); it != _channels.end(); ++it) {
	if ((*it)->getName() == name)
	  break;
      }
      if (it != _channels.end())
	_channels.erase(it);
      return true;
    }
  return false;
}

bool	Sound::ChannelGroup::remove(uint32 id) {
  Sound	*sound = getSound(id);

  if (sound)
    {
      std::vector<Channel*>::iterator it;

      for (it = _channels.begin(); it != _channels.end(); ++it) {
	if ((*it)->getId() == id)
	  break;
      }
      if (it != _channels.end())
	_channels.erase(it);
      return true;
    }
  return false;
}

bool	Sound::ChannelGroup::isPlaying(uint32 id) {
  Sound	*sound = getSound(id);

  if (sound)
    return sound->isPlaying();
  return false;
}

bool	Sound::ChannelGroup::isPlaying(std::string const& name) {
  Sound	*sound = getSound(name);

  if (sound)
    return sound->isPlaying();
  return false;
}

Sound::Sound*	Sound::ChannelGroup::getSound(std::string const& name) {
  std::vector<Channel*>::const_iterator it;  

  for (it = _channels.begin(); it != _channels.end(); ++it)
    if ((*it)->getName() == name)
      return (*it)->getSound();
  return NULL;
}

Sound::Sound*	Sound::ChannelGroup::getSound(uint32 id) {
  std::vector<Channel*>::const_iterator it;  

  for (it = _channels.begin(); it != _channels.end(); ++it)
    if ((*it)->getId() == id)
      return (*it)->getSound();
  return NULL;
}
