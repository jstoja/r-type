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
_updatePool(new Threading::ThreadPool(_updateThreadNumber)), _state(Game::Waiting), _referee(NULL) {
    _attributesMutex = new Threading::Mutex();
    _loadMap(App.getResourcesPath() + std::string("Levels/Level_1/Level_1.map"));

    if (packet) {
        *packet >> _name;
        *packet >> _nbSlots;
    }
	_viewport = new Viewport(1);

    _udpSocket = new Network::UdpSocket();
    _proxy = new Network::Proxy<Network::UdpPacket>(_udpSocket, this);
}

Game::~Game() {
    delete _udpSocket;
 	delete _viewport;
	delete _updatePool;
    delete _attributesMutex;
}

void Game::packetReceived(Network::UdpPacket* packet) {
    uint32 code, id, size;

    *packet >> code >> id >> size;
    Log("UDP Packet received 0x" << std::setfill('0') << std::setw(8) << std::hex << code);

    delete packet;
}

void Game::packetSent(Network::UdpPacket const* packet) {
    //Log("UDP Packet sent !!");
    delete packet;
}

void Game::connectionClosed(Network::Proxy<Network::UdpPacket>*) {
}


std::string const&     Game::getName(void) const {
    Threading::MutexLocker locker(_attributesMutex);
    return _name;
}

void Game::setName(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex);
    _name = name;
}


Player const*           Game::getReferee(void) const {
    return _referee;
}

void                    Game::setReferee(Player* referee) {
    _referee = referee;
}

Game::State     Game::getState(void) const {
    Threading::MutexLocker locker(_attributesMutex);
    return _state;
}

uint32                 Game::getNbPlayers(void) const {
    Threading::MutexLocker locker(_attributesMutex);
    return _players.size();
}

uint32                 Game::getNbSlots(void) const {
    Threading::MutexLocker locker(_attributesMutex);
    return _nbSlots;
}

void                    Game::setNbSlots(uint32 slots) {
    Threading::MutexLocker locker(_attributesMutex);
    _nbSlots = slots;
}

void     Game::start(void) {
    Threading::MutexLocker locker(_attributesMutex);
    _udpSocket->bind();

    // Inform players that the game starts !
    for (int i=0; i < _players.size(); i++) {
        Network::TcpPacket *packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::GameStart);
        *packet << getId() << _udpSocket->getLocalPort();
        Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
        _players[i]->sendPacket(toSend);
    }

	_state = Started;
    _clock.reset();
    _gameClock.reset();

	_viewport->setPosition(0);
	_viewport->setWidth(16);
	_viewport->setSpeed(_currentLevel.getSpeed());
}

void	Game::update() {
    Threading::MutexLocker locker(_attributesMutex);
    _proxy->checkCriticalPackets();

	_viewport->update(_clock);
	for (std::list<GameObject*>::iterator it = _objects.begin();
		it != _objects.end(); ++it)
		if (_viewport->isInViewport((*it)->getXStart()))
			_updatePool->addTask(*it, &GameObject::update, NULL);

    locker.unlock();
	_udpHandler();
    locker.relock();
    _clock.reset();
}

bool    Game::hasPlayer(Player* player) const {
    return std::find(_players.begin(), _players.end(), player) != _players.end();
}

bool    Game::canJoin(Player* player) const {
    Threading::MutexLocker locker(_attributesMutex);
    return (_nbSlots > _players.size()
            && (!player || !hasPlayer(player)));
}

void     Game::join(Player* player) {
    if (canJoin(player)) {
        Threading::MutexLocker locker(_attributesMutex);
        _players.push_back(player);
    }
}

void     Game::playerReady(Player* player) {
    Network::TcpPacket *packet = new Network::TcpPacket();
    packet->setCode(Network::TcpProxy::GamePlayerReady);
    *packet << getId() << (uint32)player->getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);

    bool everybodyReady = true;
    Threading::MutexLocker locker(_attributesMutex);
    for (int i=0; i < _players.size(); i++) {
        if (_players[i] != player) {
            _players[i]->sendPacket(toSend);
        }
        everybodyReady = everybodyReady && _players[i]->isReady();
    }
    if (_players.size() == _nbSlots && everybodyReady) {
        locker.unlock();
        start();
        locker.relock();
    }
}

void    Game::sendPlayerList(Player* player) {
    std::list<Player*> playerList;

    Threading::MutexLocker locker(_attributesMutex);
    for (int i = 0; i < _players.size(); ++i) {
        playerList.push_back(_players[i]);
    }

    Network::TcpPacket *packet = new Network::TcpPacket();

    packet->setCode(0x01020600);
    *packet << getId() << playerList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
    player->sendPacket(toSend);
}

void     Game::sendInfo(Player* player) {
    sendPlayerList(player);
}

bool     Game::quit(Player* player) {
    Threading::MutexLocker locker(_attributesMutex);
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());

    bool isReferee = (_referee == player);

    if (isReferee) {
        _referee = NULL;
    }
    return (isReferee);
}

void    Game::addGraphicElement(IGraphicElement* element) {
    Threading::MutexLocker locker(_attributesMutex);
	_graphicScene.addElement(dynamic_cast<GraphicElement*>(element));
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) {
    Threading::MutexLocker locker(_attributesMutex);
	Texture *res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);

	_gameTextures.push_back(res);
	return res;
}

ISprite*	Game::createSprite(ITexture *texture) {
	Sprite	*res = new Sprite(texture);

    Threading::MutexLocker locker(_attributesMutex);
	_gameSprites.push_back(res);
	return res;
}

ISprite*	Game::getLevelSprite(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex);
	return (_levelSprites[name]);
}

void		Game::addPhysicElement(IPhysicElement* element) {
    Threading::MutexLocker locker(_attributesMutex);
	_physicScene.addElement(dynamic_cast<PhysicElement*>(element));
}

IPhysicElement*	Game::createPhysicElement() const {
	return (new PhysicElement());
}

ISound*			Game::loadSound(std::string const& name, std::string const& pluginName) {
    Threading::MutexLocker locker(_attributesMutex);
	Sound *res= new Sound("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + name);

	_gameSounds.push_back(res);
	return res;
}

ISound*			Game::loadSound(std::string const& name) {
    Threading::MutexLocker locker(_attributesMutex);
	Sound *res= new Sound("Levels" + Application::getInstance().getDirectorySeparator() +
		_currentLevel.getFilename() + Application::getInstance().getDirectorySeparator() + name);

	_gameSounds.push_back(res);
	return res;
}

IScenery*		Game::addScenery() {
	Scenery	*res = new Scenery();

    Threading::MutexLocker locker(_attributesMutex);
	_gameSceneries.push_back(res);
	return (res);
}

void		Game::_loadMap(std::string const& fileName) {
    // Using MutexLockers to avoid duplication of unlocks in each throwing cases
    Threading::MutexLocker locker(_attributesMutex);

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
    			if (obj->init(this, it->params, it->xStart) == false)
    				throw new Exception("Cannot init plugin: " + it->name);
            locker.relock();
    			_objects.push_back(obj);
    		} catch (Exception *e) {
    			throw e;
    		} catch (...) {
    			throw new Exception("Cannot load plugin: " + it->name);
    		}
    	}
}

void	Game::sendResources(Network::TcpPacket &packet) {
    Threading::MutexLocker locker(_attributesMutex);

	std::list<Resource*>	resources;
	for (std::list<Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		resources.push_back((*it)->getImg());
	for (std::list<Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		resources.push_back((*it)->getSound());

	packet << resources << _gameTextures << _gameSprites;
	_graphicScene.sendStaticElements(packet);
	//_physicScene.sendStaticElements(packet);

	packet << _gameSceneries << _gameSounds;
}

void    Game::_sendSound(Player* player) {
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
        }
    }
}

void    Game::_sendGraphicElements(Player* player) {
    Network::UdpPacket *packet = new Network::UdpPacket();
    packet->setCode(Network::Proxy<Network::UdpPacket>::GRAPHIC_ELEMENTS);

    *packet << (float32)_gameClock.getEllapsedTime();
    _graphicScene.sendElements(*packet, _viewport);

    Network::UdpProxy::ToSend toSend(packet, player->getAddress(), player->getPort());
    _proxy->sendPacket(toSend);
}

void    Game::_sendPhysicElements(Player* player) {
    Network::UdpPacket *packet = new Network::UdpPacket();
    packet->setCode(Network::Proxy<Network::UdpPacket>::PHYSIC_ELEMENTS);
    *packet << (float32)_gameClock.getEllapsedTime();
    _physicScene.sendElements(*packet, _viewport);

    Network::UdpProxy::ToSend toSend(packet, player->getAddress(), player->getPort());
    _proxy->sendPacket(toSend);
}

void    Game::_sendTime(Player* player) {
    Network::UdpPacket* packet = new Network::UdpPacket();
    packet->setCode(Network::UdpProxy::TIME);
    *packet << (float32)_gameClock.getEllapsedTime() << (float32)_viewport->getPosition();
    Network::UdpProxy::ToSend toSend(packet, player->getAddress(), player->getPort());
    _proxy->sendPacket(toSend);
}

void    Game::_udpHandler(void) {
    Threading::MutexLocker locker(_attributesMutex);

    // Send all infos to all players
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        this->_sendTime(*it);
        this->_sendGraphicElements(*it);
    }

//    this->_sendPhysicElements();
//    this->_sendSound();
}

Network::APacket&       operator<<(Network::APacket& packet, Game const& game) {
    packet << game.getId() << game.getName() << game.getNbPlayers() << game.getNbSlots();
    return packet;
}

IViewport*	Game::getViewport() const {
    Threading::MutexLocker locker(_attributesMutex);
	return (_viewport);
}

uint64      Game::getEllapsedTime() const {
    Threading::MutexLocker lockerProxy(_attributesMutex);
    return _clock.getEllapsedTime();
}
