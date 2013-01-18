//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#include <algorithm>

#include <Application.h>
#include <Exception.h>
#include <Resource.h>

#include "Network/Proxy.hpp"
#include "Game.h"
#include "GraphicElement.h"
#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameObject.h"

Game::Game(Network::TcpPacket* packet) : _updatePool(new Threading::ThreadPool(_updateThreadNumber)), _state(Game::Waiting) {
	_loadMap("Levels/Level_1/Level_1.map");
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }

    *packet >> _name;
    *packet >> _nbSlots;
	_viewPort = new ViewPort(0.1);
}

Game::~Game() {
	delete _viewPort;
	delete _updatePool;
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

std::string const&     Game::getName(void) const {
    Threading::MutexLocker locker(_attributesMutex[eName]);
    return _name;
}

Game::State     Game::getState(void) const {
    Threading::MutexLocker locker(_attributesMutex[eState]);
    return _state;
}

uint32                 Game::getNbPlayers(void) const {
    Threading::MutexLocker locker(_attributesMutex[ePlayers]);
    return _players.size();
}

uint32                 Game::getNbSlots(void) const {
    Threading::MutexLocker locker(_attributesMutex[eNbSlots]);
    return _nbSlots;
}

void     Game::start(void) {
    _attributesMutex[ePlayers]->lock();
    for (int i=0; i < _players.size(); i++) {
        Network::TcpPacket *packet = new Network::TcpPacket();
        packet->setCode(0x01020100);
        *packet << getId();
        Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
        _players[i]->sendPacket(toSend);
        delete packet;
    }
    _attributesMutex[ePlayers]->unlock();

    //state
    _attributesMutex[eState]->lock();
	_state = Started;
    _attributesMutex[eState]->unlock();

    //clock
    _attributesMutex[eClock]->lock();
    _clock.reset();
    _attributesMutex[eClock]->unlock();

    //gameclock
    _attributesMutex[eGameClock]->lock();
    _gameClock.reset();
    _attributesMutex[eGameClock]->unlock();

    //viewport
    _attributesMutex[eViewPort]->lock();
	_viewPort->setPosition(0);
	_viewPort->setWidth(16);
	_viewPort->setSpeed(_currentLevel.getSpeed());
    _attributesMutex[eViewPort]->unlock();
}

void	Game::update() {
    _attributesMutex[eViewPort]->lock();
    _attributesMutex[eClock]->lock();
    _attributesMutex[eObjects]->lock();
    _attributesMutex[eUpdatePool]->lock();

	_viewPort->update(_clock);
	for (std::list<GameObject*>::iterator it = _objects.begin();
		it != _objects.end(); ++it)
		if (_viewPort->isInViewport((*it)->getXStart()))
			_updatePool->addTask(*it, &GameObject::update, NULL);
	//_udpHandler();
    _attributesMutex[eViewPort]->unlock();
    _attributesMutex[eClock]->unlock();
    _attributesMutex[eObjects]->unlock();
    _attributesMutex[eUpdatePool]->unlock();
}

bool     Game::canJoin(void) const {
    Threading::MutexLocker locker(_attributesMutex[ePlayers]);
    Threading::MutexLocker locker2(_attributesMutex[eNbSlots]);
    return _nbSlots > _players.size();
}

void     Game::join(Player* player) {
    if (canJoin()) {
        _attributesMutex[ePlayers]->lock();
        _players.push_back(player);

        for (int i=0; i < _players.size(); i++) {
            if (_players[i] != player) {
                Network::TcpPacket *packet = new Network::TcpPacket();
                packet->setCode(0x01020400);
                *packet << *player;
                Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
                _players[i]->sendPacket(toSend);
                delete packet;
            }
        }
        _attributesMutex[ePlayers]->unlock();
    }
}

void     Game::playerReady(Player* player) {
    Network::TcpPacket *packet = new Network::TcpPacket();
    packet->setCode(0x01020500);
    *packet << (uint32)player->getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);

    _attributesMutex[ePlayers]->lock();
    for (int i=0; i < _players.size(); i++) {
        if (_players[i] != player) {
            _players[i]->sendPacket(toSend);
        }
    }
    _attributesMutex[ePlayers]->unlock();
    delete packet;
}

void    Game::sendPlayerList(Player* player) {
    std::list<Player*> playerList;

    for (int i = 0; i < _players.size(); ++i) {
        if (_players[i] != player) {
            playerList.push_back(_players[i]);
        }
    }

    Network::TcpPacket *packet = new Network::TcpPacket();
    _attributesMutex[ePlayers]->lock();

    packet->setCode(0x01020600);
    *packet << playerList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
    player->sendPacket(toSend);
    delete packet;

    _attributesMutex[ePlayers]->unlock();
}

void     Game::sendInfo(Player* player) {
    std::list<Player*> playerList;

    for (int i = 0; i < _players.size(); ++i) {
        if (_players[i] != player) {
            playerList.push_back(_players[i]);
        }
    }

    Network::TcpPacket *packet = new Network::TcpPacket();
    packet->setCode(0x01020600);
    *packet << playerList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
    player->sendPacket(toSend);
    delete packet;

    for (int i = 0; i < _players.size(); ++i) {
        if (_players[i] != player && _players[i]->isReady()) {
            Network::TcpPacket *packet = new Network::TcpPacket();
            packet->setCode(0x01020500);
            *packet << _players[i]->getId();
            Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
            player->sendPacket(toSend);
            delete packet;
        }
    }

    _attributesMutex[ePlayers]->unlock();
}

void     Game::quit(Player* player) {
    _attributesMutex[ePlayers]->lock();
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
    _attributesMutex[ePlayers]->unlock();

}

void                Game::addGraphicElement(IGraphicElement* element) {
    _attributesMutex[eGraphicScene]->lock();
	_graphicScene.addElement(dynamic_cast<GraphicElement*>(element));
    _attributesMutex[eGraphicScene]->unlock();
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) {
    _attributesMutex[eApplication]->lock();
	Texture *res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);
    _attributesMutex[eApplication]->unlock();
    _attributesMutex[eGameTextures]->lock();
	_gameTextures.push_back(res);
    _attributesMutex[eGameTextures]->unlock();
	return res;
}

ISprite*	Game::createSprite(ITexture *texture) {
	Sprite	*res = new Sprite(texture);

    _attributesMutex[eGameSprites]->lock();
	_gameSprites.push_back(res);
    _attributesMutex[eGameSprites]->unlock();
	return res;
}

ISprite*	Game::getLevelSprite(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex[eLevelSprites]);
	return (_levelSprites[name]);
}

void		Game::addPhysicElement(IPhysicElement* element) {
    _attributesMutex[ePhysicScene]->lock();
	_physicScene.addElement(dynamic_cast<PhysicElement*>(element));
    _attributesMutex[ePhysicScene]->unlock();
}

IPhysicElement*	Game::createPhysicElement() const {
	return (new PhysicElement());
}

ISound*			Game::loadSound(std::string const& name, std::string const& pluginName) {
    _attributesMutex[eApplication]->lock();
	Sound *res= new Sound("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + name);
    _attributesMutex[eApplication]->unlock();

    _attributesMutex[eGameSounds]->lock();
	_gameSounds.push_back(res);
    _attributesMutex[eGameSounds]->unlock();
	return res;
}

ISound*			Game::loadSound(std::string const& name) {
    _attributesMutex[eApplication]->lock();
	Sound *res= new Sound("Levels" + Application::getInstance().getDirectorySeparator() +
		_currentLevel.getFilename() + Application::getInstance().getDirectorySeparator() + name);
    _attributesMutex[eApplication]->unlock();

    _attributesMutex[eGameSounds]->lock();
	_gameSounds.push_back(res);
    _attributesMutex[eGameSounds]->unlock();
	return res;
}

IScenery*		Game::addScenery() {
	Scenery	*res = new Scenery();

    _attributesMutex[eGameSceneries]->lock();
	_gameSceneries.push_back(res);
    _attributesMutex[eGameSceneries]->lock();
	return (res);
}

void		Game::_loadMap(std::string const& fileName) {
    //Using MutexLockers to avoid duplication of unlocks in each throwing cases
    Threading::MutexLocker locker(_attributesMutex[eCurrentLevel]);
    Threading::MutexLocker locker1(_attributesMutex[eLevelSprites]);
    Threading::MutexLocker locker2(_attributesMutex[eGameSprites]);
    Threading::MutexLocker locker3(_attributesMutex[eGameTextures]);

	if (_currentLevel.load(fileName) == false)
		throw new Exception("Cannot load map: " + _currentLevel.getError());
	std::list<Map::Object> const& objects = _currentLevel.getObjects();
	std::map<std::string, Texture*> const&	textures = _currentLevel.getTextures();

	_levelSprites = _currentLevel.getSprites();

	for (std::map<std::string, Texture*>::const_iterator it = textures.begin(); it != textures.end(); ++it)
		_gameTextures.push_back(it->second);

    for (std::map<std::string, Sprite*>::const_iterator it = _levelSprites.begin(); it != _levelSprites.end(); ++it)
		_gameSprites.push_back(it->second);

    for (std::list<Map::Object>::const_iterator it = objects.begin(); it != objects.end(); ++it) {
		try {
			GameObject	*obj = new GameObject(it->name);

			if (obj->init(this, it->params, it->xStart) == false)
				throw new Exception("Cannot init plugin: " + it->name);
			_objects.push_back(obj);
		} catch (Exception *e) {
			throw e;
		} catch (...) {
			throw new Exception("Cannot load plugin: " + it->name);
		}
	}
}

void	Game::sendResources(Network::TcpPacket &packet) {
    _attributesMutex[eGameTextures]->lock();
    _attributesMutex[eGameSounds]->lock();
	std::list<Resource*>	resources;
	for (std::list<Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		resources.push_back((*it)->getImg());
	for (std::list<Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		resources.push_back((*it)->getSound());

    _attributesMutex[eGameSprites]->lock();
	packet << resources << _gameTextures << _gameSprites;
    _attributesMutex[eGameSprites]->unlock();
    _attributesMutex[eGameTextures]->unlock();

    _attributesMutex[eGraphicScene]->lock();
    _attributesMutex[ePhysicScene]->lock();
	_graphicScene.sendStaticElements(packet);
	_physicScene.sendStaticElements(packet);
    _attributesMutex[eGraphicScene]->unlock();
    _attributesMutex[ePhysicScene]->unlock();

    _attributesMutex[eGameSceneries]->lock();
	packet << _gameSceneries << _gameSounds;
    _attributesMutex[eGameSceneries]->unlock();
    _attributesMutex[eGameSounds]->unlock();

}

// void    Game::_sendSound(void) {
//     _attributesMutex[eGameSounds]->lock();
//     _attributesMutex[ePlayers]->lock();

//     for (std::list<Sound*>::const_iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it) {
//         if ((*it)->hasChanged()) {
//             Network::UdpPacket *udpPacket = new Network::UdpPacket();
//             *udpPacket << (*it)->getId();

//             if ((*it)->isPlaying()) {
//                 udpPacket->setCode(Network::Proxy<Network::UdpPacket>::PLAY_SOUND);
//             } else {
//                 udpPacket->setCode(Network::Proxy<Network::UdpPacket>::STOP_SOUND);
//             }
//             Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

//             for (int i=0; i < _players.size(); i++) {
//                 _players[i]->sendPacket(toSend);
//             }
//             (*it)->setChanged(false);
//             delete udpPacket;
//         }
//     }
//     _attributesMutex[eGameSounds]->unlock();
//     _attributesMutex[ePlayers]->unlock();
// }

// void    Game::_sendGraphicElements(void) {
//     Network::UdpPacket *udpPacket = new Network::UdpPacket();
//     udpPacket->setCode(Network::Proxy<Network::UdpPacket>::GRAPHIC_ELEMENTS);
//     _attributesMutex[eGraphicScene]->lock();
//     _attributesMutex[eViewPort]->lock();
//     _graphicScene.sendElements(*udpPacket, _viewPort);
//     _attributesMutex[eGraphicScene]->unlock();
//     _attributesMutex[eViewPort]->unlock();


//     Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

//     _attributesMutex[ePlayers]->lock();
//     for (int i=0; i < _players.size(); i++) {
//         _players[i]->sendPacket(toSend);
//     }
//     _attributesMutex[ePlayers]->unlock();
//     delete udpPacket;
// }

// void    Game::_sendPhysicElements(void) {
//     Network::UdpPacket *udpPacket = new Network::UdpPacket();
//     udpPacket->setCode(Network::Proxy<Network::UdpPacket>::PHYSIC_ELEMENTS);
//     _attributesMutex[ePhysicScene]->lock();
//     _attributesMutex[eViewPort]->lock();
//     _physicScene.sendElements(*udpPacket, _viewPort);
//     _attributesMutex[ePhysicScene]->unlock();
//     _attributesMutex[eViewPort]->unlock();
//     Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

//     _attributesMutex[ePlayers]->lock();
//     for (int i=0; i < _players.size(); i++) {
//         _players[i]->sendPacket(toSend);
//     }
//     _attributesMutex[ePlayers]->unlock();
//     delete udpPacket;
// }

// void    Game::_sendTime(void) {
//     Network::UdpPacket *udpPacket = new Network::UdpPacket();
// 	udpPacket->setCode(Network::Proxy<Network::UdpPacket>::TIME);
// 	*udpPacket << _gameClock.getEllapsedTime();
//     Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

//     for (int i=0; i < _players.size(); i++) {
//         _players[i]->sendPacket(toSend);
//     }
//     delete udpPacket;
// }

// void    Game::_udpHandler(void) {
// 	this->_sendTime();
//     this->_sendGraphicElements();
//     this->_sendPhysicElements();
//     this->_sendSound();
// }

Network::APacket&       operator<<(Network::APacket& packet, Game const& game) {
    packet << game.getId() << game.getName() << game.getNbPlayers() << game.getNbSlots();
    return packet;
}

IViewPort*	Game::getViewPort() const {
    Threading::MutexLocker locker(_attributesMutex[eViewPort]);
	return (_viewPort);
}