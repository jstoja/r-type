//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#include <algorithm>

#include <Application.h>
#include <Exception.h>
#include <Resource.h>
#include <algorithm>

#include "Network/Proxy.hpp"
#include "Game.h"
#include "GraphicElement.h"
#include "Player.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameObject.h"

Game::Game(Network::TcpPacket* packet) :
_attributesMutex(), _players(), _nbSlots(0), _name(), _currentLevel(),
_updatePool(new Threading::ThreadPool(_updateThreadNumber)), _state(Game::Waiting) {
    _attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
	_loadMap(App.getResourcesPath() + std::string("Levels/Level_1/Level_1.map"));

    if (packet) {
        *packet >> _name;
        *packet >> _nbSlots;
    }
	_viewPort = new ViewPort(0.1);

    Network::UdpSocket *_udpSocket = new Network::UdpSocket();
    _proxy = new Network::Proxy<Network::UdpPacket>(_udpSocket, this);
}

Game::~Game() {
 	delete _viewPort;
	delete _updatePool;
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void Game::packetReceived(Network::UdpPacket* packet) {
    uint32 code, id, size;

    *packet >> code >> id >> size;
    Log("UDP Packet received 0x" << std::setfill('0') << std::setw(8) << std::hex << code);

    delete packet;
}

void Game::packetSent(Network::UdpPacket const* packet) {
    delete packet;
}

void Game::connectionClosed(Network::Proxy<Network::UdpPacket>*) {
}


std::string const&     Game::getName(void) const {
    Threading::MutexLocker locker(_attributesMutex[eName]);
    return _name;
}

void Game::setName(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex[eName]);
    _name = name;
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

void                    Game::setNbSlots(uint32 slots) {
    Threading::MutexLocker locker(_attributesMutex[eNbSlots]);
    _nbSlots = slots;
}

void     Game::start(void) {
    Threading::MutexLocker lockerPlayer(_attributesMutex[ePlayers]);
    // Inform players that the game starts !
    for (int i=0; i < _players.size(); i++) {
        Network::TcpPacket *packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::GameStart);
        *packet << getId();
        Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
        _players[i]->sendPacket(toSend);
    }
    lockerPlayer.unlock();

    //state
    Threading::MutexLocker lockerState(_attributesMutex[eState]);
	_state = Started;
    lockerState.unlock();

    //clock
    Threading::MutexLocker lockerClock(_attributesMutex[eClock]);
    _clock.reset();
    lockerClock.unlock();

    //gameclock
    Threading::MutexLocker lockerGameClock(_attributesMutex[eGameClock]);
    _gameClock.reset();
    lockerGameClock.unlock();

    //viewport
    Threading::MutexLocker lockerViewport(_attributesMutex[eViewPort]);
    Threading::MutexLocker lockerCurrentLevel(_attributesMutex[eCurrentLevel]);
	_viewPort->setPosition(0);
	_viewPort->setWidth(16);
	_viewPort->setSpeed(_currentLevel.getSpeed());
}

void	Game::update() {
    _proxy->checkCriticalPackets();

    Threading::MutexLocker lockerViewport(_attributesMutex[eViewPort]);
    Threading::MutexLocker lockerObjects(_attributesMutex[eObjects]);
    Threading::MutexLocker lockerClock(_attributesMutex[eClock]);
    Threading::MutexLocker lockerUpdatePool(_attributesMutex[eUpdatePool]);

	_viewPort->update(_clock);
	for (std::list<GameObject*>::iterator it = _objects.begin();
		it != _objects.end(); ++it)
		if (_viewPort->isInViewport((*it)->getXStart()))
			_updatePool->addTask(*it, &GameObject::update, NULL);
	//_udpHandler();
}

bool    Game::hasPlayer(Player* player) const {
    return std::find(_players.begin(), _players.end(), player) != _players.end();
}

bool    Game::canJoin(Player* player) const {
    Threading::MutexLocker locker(_attributesMutex[ePlayers]);
    Threading::MutexLocker locker2(_attributesMutex[eNbSlots]);
    return (_nbSlots > _players.size()
            && (!player || !hasPlayer(player)));
}

void     Game::join(Player* player) {
    if (canJoin(player)) {
        Threading::MutexLocker lockerPlayers(_attributesMutex[ePlayers]);
        _players.push_back(player);
    }
}

void     Game::playerReady(Player* player) {
    Network::TcpPacket *packet = new Network::TcpPacket();
    packet->setCode(Network::TcpProxy::GamePlayerReady);
    *packet << getId() << (uint32)player->getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);

    bool everybodyReady = true;
    Threading::MutexLocker lockerPlayers(_attributesMutex[ePlayers]);
    for (int i=0; i < _players.size(); i++) {
        if (_players[i] != player) {
            _players[i]->sendPacket(toSend);
        }
        everybodyReady = everybodyReady && _players[i]->isReady();
    }
    if (everybodyReady)
        start();
}

void    Game::sendPlayerList(Player* player) {
    std::list<Player*> playerList;
    
    Threading::MutexLocker lockerPlayers(_attributesMutex[ePlayers]);
    for (int i = 0; i < _players.size(); ++i) {
        playerList.push_back(_players[i]);
    }
    lockerPlayers.unlock();
    
    Network::TcpPacket *packet = new Network::TcpPacket();

    packet->setCode(0x01020600);
    *packet << getId() << playerList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
    player->sendPacket(toSend);
}

void     Game::sendInfo(Player* player) {
    sendPlayerList(player);
}

void     Game::quit(Player* player) {
    Threading::MutexLocker lockerPlayers(_attributesMutex[ePlayers]);
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
}

void    Game::addGraphicElement(IGraphicElement* element) {
    Threading::MutexLocker lockerGraphic(_attributesMutex[eGraphicScene]);
	_graphicScene.addElement(dynamic_cast<GraphicElement*>(element));
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) {
    Threading::MutexLocker lockerApplication(_attributesMutex[eApplication]);
	Texture *res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);
    lockerApplication.unlock();
    
    Threading::MutexLocker lockerGame(_attributesMutex[eGameTextures]);
	_gameTextures.push_back(res);
	return res;
}

ISprite*	Game::createSprite(ITexture *texture) {
	Sprite	*res = new Sprite(texture);

    Threading::MutexLocker lockerGame(_attributesMutex[eGameSprites]);
	_gameSprites.push_back(res);
	return res;
}

ISprite*	Game::getLevelSprite(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex[eLevelSprites]);
	return (_levelSprites[name]);
}

void		Game::addPhysicElement(IPhysicElement* element) {
    Threading::MutexLocker lockerPhysic(_attributesMutex[ePhysicScene]);
	_physicScene.addElement(dynamic_cast<PhysicElement*>(element));
}

IPhysicElement*	Game::createPhysicElement() const {
	return (new PhysicElement());
}

ISound*			Game::loadSound(std::string const& name, std::string const& pluginName) {
    Threading::MutexLocker lockerApplication(_attributesMutex[eApplication]);
	Sound *res= new Sound("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + name);
    lockerApplication.unlock();
    
    Threading::MutexLocker lockerSounds(_attributesMutex[eGameSounds]);
	_gameSounds.push_back(res);
	return res;
}

ISound*			Game::loadSound(std::string const& name) {
    Threading::MutexLocker lockerApplication(_attributesMutex[eApplication]);
	Sound *res= new Sound("Levels" + Application::getInstance().getDirectorySeparator() +
		_currentLevel.getFilename() + Application::getInstance().getDirectorySeparator() + name);
    lockerApplication.unlock();

    Threading::MutexLocker lockerSounds(_attributesMutex[eGameSounds]);
	_gameSounds.push_back(res);
	return res;
}

IScenery*		Game::addScenery() {
	Scenery	*res = new Scenery();

    Threading::MutexLocker lockerGame(_attributesMutex[eGameSceneries]);
	_gameSceneries.push_back(res);
	return (res);
}

void		Game::_loadMap(std::string const& fileName) {
    // Using MutexLockers to avoid duplication of unlocks in each throwing cases
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

            locker.unlock();
            locker1.unlock();
            locker2.unlock();
            locker3.unlock();
			if (obj->init(this, it->params, it->xStart) == false)
				throw new Exception("Cannot init plugin: " + it->name);
            locker.relock();
            locker1.relock();
            locker2.relock();
            locker3.relock();
			_objects.push_back(obj);
		} catch (Exception *e) {
			throw e;
		} catch (...) {
			throw new Exception("Cannot load plugin: " + it->name);
		}
	}
}

void	Game::sendResources(Network::TcpPacket &packet) {
    Threading::MutexLocker lockerGameTextures(_attributesMutex[eGameTextures]);
    Threading::MutexLocker lockerGameSounds(_attributesMutex[eGameSounds]);

	std::list<Resource*>	resources;
	for (std::list<Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		resources.push_back((*it)->getImg());
	for (std::list<Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		resources.push_back((*it)->getSound());

    Threading::MutexLocker lockerGameSprites(_attributesMutex[eGameSprites]);
	packet << resources << _gameTextures << _gameSprites;
    lockerGameSprites.unlock();
    lockerGameTextures.unlock();

    Threading::MutexLocker lockerGraphicScene(_attributesMutex[eGraphicScene]);
    Threading::MutexLocker lockerPhysicScene(_attributesMutex[ePhysicScene]);
	_graphicScene.sendStaticElements(packet);
	//_physicScene.sendStaticElements(packet);
    lockerGraphicScene.unlock();
    lockerPhysicScene.unlock();

    Threading::MutexLocker lockerGameSceneries(_attributesMutex[eGameSceneries]);
	packet << _gameSceneries << _gameSounds;
}

void    Game::_sendSound(void) {
    Threading::MutexLocker lockerGameSounds(_attributesMutex[eGameSounds]);

    for (std::list<Sound*>::const_iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it) {
        if ((*it)->hasChanged()) {
            Network::UdpPacket *udpPacket = new Network::UdpPacket();
            *udpPacket << (*it)->getId();

            if ((*it)->isPlaying()) {
                udpPacket->setCode(Network::Proxy<Network::UdpPacket>::PLAY_SOUND);
            } else {
                udpPacket->setCode(Network::Proxy<Network::UdpPacket>::STOP_SOUND);
            }
            Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);
            _proxy->sendPacket(toSend);
            (*it)->setChanged(false);
            delete udpPacket;
        }
    }
    _attributesMutex[eGameSounds]->unlock();
}

void    Game::_sendGraphicElements(void) {
    Network::UdpPacket *udpPacket = new Network::UdpPacket();
    udpPacket->setCode(Network::Proxy<Network::UdpPacket>::GRAPHIC_ELEMENTS);
    Threading::MutexLocker lockerGraphicScene(_attributesMutex[eGraphicScene]);
    Threading::MutexLocker lockerViewport(_attributesMutex[eViewPort]);

    _graphicScene.sendElements(*udpPacket, _viewPort);
    lockerGraphicScene.unlock();
    lockerViewport.unlock();

    Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);
    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy->sendPacket(toSend);
    delete udpPacket;
}

void    Game::_sendPhysicElements(void) {
    Network::UdpPacket *udpPacket = new Network::UdpPacket();
    udpPacket->setCode(Network::Proxy<Network::UdpPacket>::PHYSIC_ELEMENTS);
    Threading::MutexLocker lockerPhysic(_attributesMutex[ePhysicScene]);
    Threading::MutexLocker lockerViewport(_attributesMutex[eViewPort]);
    _physicScene.sendElements(*udpPacket, _viewPort);
    lockerPhysic.unlock();
    lockerViewport.unlock();
    
    Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);
    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy->sendPacket(toSend);
    delete udpPacket;
}

void    Game::_sendTime(void) {
    Network::UdpPacket *udpPacket = new Network::UdpPacket();
	udpPacket->setCode(Network::Proxy<Network::UdpPacket>::TIME);
    Threading::MutexLocker lockerGameClock(_attributesMutex[eGameClock]);
	*udpPacket << _gameClock.getEllapsedTime();
    lockerGameClock.unlock();
    
    Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);
    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy->sendPacket(toSend);
    delete udpPacket;
}

void    Game::_udpHandler(void) {
	this->_sendTime();
    this->_sendGraphicElements();
    this->_sendPhysicElements();
    this->_sendSound();
}

Network::APacket&       operator<<(Network::APacket& packet, Game const& game) {
    packet << game.getId() << game.getName() << game.getNbPlayers() << game.getNbSlots();
    return packet;
}

IViewPort*	Game::getViewPort() const {
    Threading::MutexLocker locker(_attributesMutex[eViewPort]);
	return (_viewPort);
}

uint64      Game::getEllapsedTime() const {
    Threading::MutexLocker lockerProxy(_attributesMutex[eClock]);
    return _clock.getEllapsedTime();
}