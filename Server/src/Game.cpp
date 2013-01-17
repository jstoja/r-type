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

Game::Game(Network::TcpPacket* packet) : _updatePool(new Threading::ThreadPool(_updateThreadNumber)), _state(Game::WAITING) {
    *packet >> _name;
    *packet >> _nbSlots;
	_viewPort = new ViewPort(0.1);
}

Game::~Game() {
	delete _viewPort;
	delete _updatePool;
}

std::string const&     Game::getName(void) const {
    return _name;
}

Game::State     Game::getState(void) const {
    return _state;
}

uint32                 Game::getNbPlayers(void) const {
    return _players.size();
}

uint32                 Game::getNbSlots(void) const {
    return _nbSlots;
}

void     Game::start(void) {
    for (int i=0; i < _players.size(); i++) {
        Network::TcpPacket *packet = new Network::TcpPacket();
        packet->setCode(0x01020100);
        *packet << getId();
        Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
        _players[i]->sendPacket(toSend);
        delete packet;
    }
	_state = STARTED;
	_clock.reset();
	_gameClock.reset();
	_viewPort->setPosition(0);
	_viewPort->setWidth(16);
}

void	Game::update() {
	_viewPort->update(_clock);
	for (std::list<GameObject*>::iterator it = _objects.begin();
		it != _objects.end(); ++it)
		if (_viewPort->isInViewport((*it)->getXStart()))
			_updatePool->addTask(*it, &GameObject::update, NULL);
}

bool     Game::canJoin(void) const {
    return _nbSlots > _players.size();
}

void     Game::join(Player* player) {
    if (canJoin()) {
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
    }
}

void     Game::playerReady(Player* player) {
    Network::TcpPacket *packet = new Network::TcpPacket();
    packet->setCode(0x01020500);
    *packet << (uint32)player->getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);

    for (int i=0; i < _players.size(); i++) {
        if (_players[i] != player) {
            _players[i]->sendPacket(toSend);
        }
    }
    delete packet;
}

void     Game::quit(Player* player) {
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
}

void                Game::addGraphicElement(IGraphicElement* element) {
	_graphicScene.addElement(dynamic_cast<GraphicElement*>(element));
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) {
	Texture *res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);
	_gameTextures.push_back(res);
	return res;
}

ISprite*	Game::createSprite(ITexture *texture) {
	Sprite	*res = new Sprite(texture);
	_gameSprites.push_back(res);
	return res;
}

ISprite*	Game::getLevelSprite(std::string const& name) {
	return (_levelSprites[name]);
}

void		Game::addPhysicElement(IPhysicElement* element) {
	_physicScene.addElement(dynamic_cast<PhysicElement*>(element));
}

IPhysicElement*	Game::createPhysicElement() const {
	return (new PhysicElement());
}

ISound*			Game::loadSound(std::string const& name, std::string const& pluginName) {
	Sound *res= new Sound("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + name);
	_gameSounds.push_back(res);
	return res;
}

ISound*			Game::loadSound(std::string const& name) {
	Sound *res= new Sound("Levels" + Application::getInstance().getDirectorySeparator() +
		_currentLevel.getFilename() + Application::getInstance().getDirectorySeparator() + name);
	_gameSounds.push_back(res);
	return res;
}

IScenery*		Game::addScenery() {
	Scenery	*res = new Scenery();
	_gameSceneries.push_back(res);
	return (res);
}

void		Game::loadMap(std::string const& fileName) {
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
	std::list<Resource*>	resources;
	for (std::list<Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		resources.push_back((*it)->getImg());
	for (std::list<Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		resources.push_back((*it)->getSound());
	packet << resources << _gameTextures << _gameSprites;
	_graphicScene.sendStaticElements(packet);
	_physicScene.sendStaticElements(packet);
	packet << _gameSceneries << _gameSounds;
}

void    Game::_sendSound(void) {
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

            for (int i=0; i < _players.size(); i++) {
                _players[i]->sendPacket(toSend);
            }
            (*it)->setChanged(false);
            delete udpPacket;
        }
    }
}

void    Game::_sendGraphicElements(void) {
    Network::UdpPacket *udpPacket = new Network::UdpPacket();
    udpPacket->setCode(Network::Proxy<Network::UdpPacket>::GRAPHIC_ELEMENTS);
    _graphicScene.sendElements(*udpPacket, _viewPort);
    Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

    for (int i=0; i < _players.size(); i++) {
        _players[i]->sendPacket(toSend);
    }
    delete udpPacket;
}

void    Game::_sendPhysicElements(void) {
    Network::UdpPacket *udpPacket = new Network::UdpPacket();
    udpPacket->setCode(Network::Proxy<Network::UdpPacket>::PHYSIC_ELEMENTS);
    _physicScene.sendElements(*udpPacket, _viewPort);
    Network::Proxy<Network::UdpPacket>::ToSend toSend(udpPacket, Network::HostAddress::AnyAddress, 0);

    for (int i=0; i < _players.size(); i++) {
        _players[i]->sendPacket(toSend);
    }
    delete udpPacket;
}

void    Game::udpHandler(void) {
    this->_sendGraphicElements();
    this->_sendPhysicElements();
    this->_sendSound();
}

Network::APacket&       operator<<(Network::APacket& packet, Game const& game) {
    packet << game.getId() << game.getName() << game.getNbPlayers() << game.getNbSlots();
    return packet;
}

IViewPort*	Game::getViewPort() const {
	return (_viewPort);
}