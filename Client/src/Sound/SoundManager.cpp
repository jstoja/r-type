//
//  SoundManager.cpp
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//
#include "Channel.h"
#include "ChannelGroup.h"
#include "Sound.h"
#include "SoundManager.h"
#include "ResourcesManager.h"
#include "Resource.h"

#ifndef OS_IOS
template <> Sound::SoundManager*	Singleton<Sound::SoundManager>::_instance = new Sound::SoundManager();
#endif

Sound::SoundManager::SoundManager() {  
}

Sound::SoundManager::~SoundManager() {
}

void    Sound::SoundManager::load(Resource* resource) {
    std::list<ChannelGroup*>::iterator it;
    Sound		*snd = new Sound(resource);
    
	_soundsName[snd->getName()] = snd;
	_soundsId[snd->getId()] = snd;
    
	for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
		if ((*it)->load(snd) == true) {
			break;
		}
	}
	if (it == _channelsGroups.end()) {
		_channelsGroups.push_back(new ChannelGroup());
		_channelsGroups.back()->load(snd);
	}
}

void	Sound::SoundManager::load(std::string const& name) {
	std::list<ChannelGroup*>::iterator it;
    ResourcesManager& manager = ResourcesManager::getInstance();
    Resource*  resource = manager.getResource(name);
    Sound		*snd = new Sound(resource);

	_soundsName[name] = snd;
	_soundsId[snd->getId()] = snd;

	for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
		if ((*it)->load(snd) == true) {
			break;
		}
	}
	if (it == _channelsGroups.end()) {
		_channelsGroups.push_back(new ChannelGroup());
		_channelsGroups.back()->load(snd);
	}
}

void	Sound::SoundManager::load(uint32 id) {
	std::list<ChannelGroup*>::iterator it;
    ResourcesManager manager = ResourcesManager::getInstance();
    Resource*  resource = manager.getResource(id);    
    Sound		*snd = new Sound(resource);
    
	_soundsName[snd->getName()] = snd;
	_soundsId[snd->getId()] = snd;
    
	for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
		if ((*it)->load(snd) == true) {
			break;
		}
	}
	if (it == _channelsGroups.end()) {
		_channelsGroups.push_back(new ChannelGroup());
		_channelsGroups.back()->load(snd);
	}
}

void	Sound::SoundManager::remove(std::string const& name) {
	std::list<ChannelGroup*>::iterator it;
	Sound *item = getSound(name);

	if (item != NULL) {
		_soundsId.erase(item->getId());
		_soundsName.erase(item->getName());
		for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
			if ((*it)->remove(name) == true) {
				break;
			}
		}
	}
}

void	Sound::SoundManager::remove(uint32 id) {
	std::list<ChannelGroup*>::iterator it;
	Sound *item = getSound(id);

	if (item != NULL) {
		_soundsId.erase(item->getId());
		_soundsName.erase(item->getName());
		for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
			if ((*it)->remove(id) == true) {
				break;
			}
		}
	}
}

void	Sound::SoundManager::play(std::string const& name) {  
	std::list<ChannelGroup*>::iterator it;
	Sound *item = getSound(name);

	if (item != NULL) {
		for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
			if ((*it)->play(name) == true) {
				break;
			}
		}
	}
}

void	Sound::SoundManager::play(uint32 id) {
	std::list<ChannelGroup*>::iterator it;
	Sound *item = getSound(id);

	if (item != NULL) {
		for (it = _channelsGroups.begin(); it != _channelsGroups.end(); ++it) {
			if ((*it)->play(id) == true) {
				break;
			}
		}
	}
}

Sound::Sound	*Sound::SoundManager::getSound(uint32 id) {
	std::map<uint32, Sound*>::const_iterator it;  

	if ((it = _soundsId.find(id)) != _soundsId.end()) {
		return it->second;
	}
	return NULL;
}

Sound::Sound	*Sound::SoundManager::getSound(std::string const& name) {
	std::map<std::string, Sound*>::const_iterator it;  

	if ((it = _soundsName.find(name)) != _soundsName.end()) {
		return it->second;
	}
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
