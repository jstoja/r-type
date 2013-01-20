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

  _commands[Network::UdpProxy::PLAYER_DIRECTION] = &Game::updatePlayerDirection;
  _commands[Network::UdpProxy::PLAYER_SHOOT] = &Game::playerShoot;
  _commands[Network::UdpProxy::PHYSIC_COLLISION] = &Game::physicCollision;

    _attributesMutex = new Threading::Mutex();
    _loadMap(App.getResourcesPath() + std::string("Levels/Level_1/Level_1.map"));

    if (packet) {
        *packet >> _name;
        *packet >> _nbSlots;
    }
	_viewport = new Viewport(1);

    _udpSocket = new Network::UdpSocket();
    _proxy = new Network::Proxy<Network::UdpPacket>(_udpSocket, this);
    
    _playerSprite = createSprite(createTexture("player.png"));
    _playerSprite->addFrame(Vec2(65.0/330.0, 0), Vec2(65.0*2/330.0, 34.0/170.0));
}

Game::~Game() {
    delete _udpSocket;
 	delete _viewport;
	delete _updatePool;
    delete _attributesMutex;
}

void Game::packetReceived(Network::UdpPacket* packet) {
    uint32 code;

    *packet >> code;
    std::map<int, commandPointer>::iterator it = _commands.find(code);
    if (it != _commands.end())
      (this->*(it->second))(packet);
    else {
      Log("Received unknown command 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
    }
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

    _updatePlayers();
    
    locker.unlock();
	_udpHandler();
    locker.relock();
    
    _graphicScene.updateFinished();
    _physicScene.updateFinished();
    
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
        // Create player graphic and physic element
        GraphicElement* element = new GraphicElement();
        element->setPosition(Vec2(16.0/2, 9.0/2));
        element->setSize(Vec2(0.8125, 0.425));
        element->setType(IGraphicElement::Dynamic);
        _playersGraphicElements[player] = element;
        element->setSprite(_playerSprite);
        element->setSpriteFrameIndex(0);
        _graphicScene.addElement(element);
        PhysicElement* physic = new PhysicElement();
        physic->setPosition(Vec2(16.0/2, 9.0/2));
        physic->setSize(Vec2(0.8125, 0.425));
        _physicScene.addElement(physic);
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

    _graphicScene.removeElement(_playersGraphicElements[player]);
    delete _playersGraphicElements[player];
    _playersGraphicElements.erase(player);

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
	Texture *res;
    if (!pluginName.empty()) {
        res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator()
                          + pluginName + Application::getInstance().getDirectorySeparator()
                          + filename);
    } else {
        res = new Texture(filename);
    }
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

void        Game::createObject(std::string const &objectName, ByteArray const& params, float32 xStart) {
    GameObject	*obj = new GameObject(objectName);
    if (obj->init(this, params, xStart) == false)
        throw new Exception("Cannot init plugin: " + objectName);

    Threading::MutexLocker locker(_attributesMutex);
    _objects.push_back(obj);
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

void    Game::_updatePlayers(void) {
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        // Update players
        (*it)->update(_clock.getEllapsedTime());
        
        // And their graphic elements
        Vec3 pos = Vec3(_viewport->getPosition(), 0,
                        _playersGraphicElements[*it]->getPosition().z);
        pos = pos + Vec3((*it)->getPosition(), 0);
        _playersGraphicElements[*it]->setPosition(pos);
    }
}

void    Game::_udpHandler(void) {
    Threading::MutexLocker locker(_attributesMutex);

    // Send all infos to all players
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        this->_sendTime(*it);
        this->_sendGraphicElements(*it);
        this->_sendPhysicElements(*it);
    }

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

#pragma mark Protocol udp calls

void Game::updatePlayerDirection(Network::UdpPacket* packet) {
    Threading::MutexLocker locker(_attributesMutex);

    Vec2 speed;
    *packet >> speed;
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        if ((*it)->getPort() == packet->getPort() &&
            (*it)->getAddress() == packet->getAddress()) {
            (*it)->updateSpeed(speed);
        }
    }
}

void Game::playerShoot(Network::UdpPacket*) {

}

void Game::physicCollision(Network::UdpPacket*) {

}
