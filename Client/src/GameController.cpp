//
//  GameController.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/01/13.
//
//

#include "GameController.h"

#include "Event/Manager.h"
#include "ObjectManager.h"

GameController::GameController(Game* game, Graphic::Scene* scene) :
_game(game), _gameLaunched(false), _scene(scene), _eventListener(NULL),
_udpSocket(NULL), _udpProxy(NULL) {

  _commands[Network::TcpProxy::GRAPHIC_ELEMENTS] = &GameController::receiveGraphicElements;
  _commands[Network::TcpProxy::PHYSIC_ELEMENTS] = &GameController::receivePhysicElements;
  _commands[Network::TcpProxy::PLAY_SOUND] = &GameController::playSound;
  _commands[Network::TcpProxy::STOP_SOUND] = &GameController::stopSound;
  _commands[Network::TcpProxy::TIME] = &GameController::updateTime;
  _commands[Network::TcpProxy::UPDATE_LIFE] = &GameController::updateLife;
  _commands[Network::TcpProxy::UPDATE_SCORE] = &GameController::updateScore;
  _commands[Network::TcpProxy::GAME_FINISHED] = &GameController::gameFinished;

    // Create the event listener to get user input
    _eventListener = new Event::Listener(Event::KeyPressed | Event::KeyReleased, this);
    Event::Manager::getInstance().addEventListener(_eventListener);
    
    _udpSocket = new Network::UdpSocket();
    _udpSocket->bind();
    _udpPort = _udpSocket->getLocalPort();
    _udpProxy = new Network::UdpProxy(_udpSocket, this);    
}

GameController::~GameController(void) {
    Event::Manager::getInstance().removeEventListener(_eventListener);
    delete _eventListener;
    delete _udpProxy;
    delete _udpSocket;
}

#pragma mark Event listener delegate methods

void GameController::processEvent(Event::Event const& event) {
    if (event.type & (Event::KeyPressed | Event::KeyReleased)) {
        
    }
}

#pragma mark UDP proxy delegate methods

void GameController::packetReceived(Network::UdpPacket* packet) {
    uint32 code;

    *packet >> code;    
    std::map<int, commandPointer>::iterator it = _commands.find(code);
    if (it != _commands.end())
      (this->*(it->second))(packet);
    else
      Log("Received unknown command 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
    delete packet;

    //Log("UDP Packet received 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
}

void GameController::packetSent(Network::UdpPacket const* packet) {
    
}

void GameController::connectionClosed(Network::Proxy<Network::UdpPacket>* proxy) {
    
}

void GameController::packetInProgress(uint32 code, float32 progress) {
    
}

#pragma mark Game creation

void GameController::receiveResources(Network::TcpPacket* packet) {
    uint32 nb;
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Resource* resource = createResource(*packet);
		if (resource)
			_resources.push_back(resource);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Texture* texture = createTexture(*packet);
		if (texture)
			_textures.push_back(texture);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Sprite* sprite = createSprite(*packet);
		if (sprite)
			_sprites.push_back(sprite);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Element* element = createGraphicElement(*packet);
		if (element)
			_elements.push_back(element);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Scenery* scenery = createScenery(*packet);
		if (scenery) {
			_sceneries.push_back(scenery);
		}
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Sound::Sound* sound = createSound(*packet);
		if (sound)
			_sounds.push_back(sound);
    }
}

Resource* GameController::createResource(Network::TcpPacket& packet) {
	uint32		id;
	Resource	*res;
	ByteArray	data;
    
	packet >> id >> data;
	res = new Resource(id);
	res->setData(data);
	return (res);
}

Graphic::Texture* GameController::createTexture(Network::TcpPacket& packet) {
	uint32		id, resourceId;
    
	packet >> id >> resourceId;
	Resource *resource = dynamic_cast<Resource*>(ObjectManager::getInstance().getObject(resourceId));
	if (resource)
		return (new Graphic::Texture(id, resource));
	return (NULL);
}

Graphic::Sprite* GameController::createSprite(Network::TcpPacket& packet) {
	uint32		id, textureId;
    
	packet >> id >> textureId;
	Graphic::Texture *texture = dynamic_cast<Graphic::Texture*>(ObjectManager::getInstance().getObject(textureId));
	if (texture) {
		std::list<Graphic::Sprite::Frame> frames;
        
		packet >> frames;
		Graphic::Sprite* res = new Graphic::Sprite(id);
		res->setTexture(texture);
		for (std::list<Graphic::Sprite::Frame>::iterator it = frames.begin(); it != frames.end(); ++it)
			res->addFrame(*it);
		return (res);
	}
	return (NULL);
}

Graphic::Element* GameController::createGraphicElement(Network::TcpPacket& packet) {
	uint32 id, spriteId;
	Vec3 position;
	float32 rotation;
	Vec2 size;
	char spriteFrame, type;
    
	packet >> id >> position >> rotation >> size >> spriteId >> spriteFrame >> type;
	Graphic::Sprite* sprite = dynamic_cast<Graphic::Sprite*>(ObjectManager::getInstance().getObject(spriteId));
	if (sprite) {
		Graphic::Element* res = new Graphic::Element(id);
		res->setPosition(position);
		res->setRotation(rotation);
		res->setSize(size);
		res->setSprite(sprite);
		res->setCurrentFrame(spriteFrame);
		Graphic::Element::Type newType = Graphic::Element::Dynamic;
		if (type == 0)
			newType = Graphic::Element::Static;
		else if (type == 2)
			newType = Graphic::Element::Floating;
		res->setType(newType);
		return (res);
	}
	return (NULL);
}

Graphic::Scenery* GameController::createScenery(Network::TcpPacket& packet) {
	uint32 id, textureId;
	float32 speed, width, xStart, xEnd, depth, opacity;
    
	packet >> id >> textureId >> speed >> width >> xStart >> xEnd >> depth >> opacity;
	Graphic::Texture *texture = dynamic_cast<Graphic::Texture*>(ObjectManager::getInstance().getObject(textureId));
	if (texture) {
		Graphic::Scenery*	res = new Graphic::Scenery(id);
		res->setTexture(texture);
		res->setSpeed(speed);
		res->setWidth(width);
		res->setRange(Vec2(xStart, xEnd));
		res->setDepth(depth);
		res->setOpacity(opacity);
		return (res);
	}
	return (NULL);
}

Sound::Sound* GameController::createSound(Network::TcpPacket& packet) {
	uint32	id, resourceId;
	int32	repeat;
    
	packet >> id >> resourceId >> repeat;
	Resource *resource = dynamic_cast<Resource*>(ObjectManager::getInstance().getObject(resourceId));
	if (resource) {
		Sound::Sound* res = new Sound::Sound(resource);
		return (res);
	}
	return (NULL);
}

#pragma mark Game actions

void GameController::launchGame(void) {
	for (std::list<Graphic::Element*>::iterator it = _elements.begin(); it != _elements.end(); ++it) {
		if (*it) {
			(*it)->setVisible(true);
			_scene->addElement(*it);
		}
	}
	for (std::list<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it) {
		if (*it) {
			_scene->addScenery(*it);
		}
	}
    _scene->setViewportPosition(Vec2(0, 0));
    _gameLaunched = true;
}

void GameController::clearGame(void) {
	for (std::list<Resource*>::iterator it = _resources.begin(); it != _resources.end(); ++it)
		delete *it;
	_resources.clear();
	for (std::list<Graphic::Texture*>::iterator it = _textures.begin(); it != _textures.end(); ++it)
		delete *it;
	_textures.clear();
	for (std::list<Graphic::Sprite*>::iterator it = _sprites.begin(); it != _sprites.end(); ++it)
		delete *it;
	_sprites.clear();
	for (std::list<Graphic::Element*>::iterator it = _elements.begin(); it != _elements.end(); ++it) {
		_scene->removeElement(*it);
		delete *it;
	}
	_elements.clear();
	for (std::list<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it) {
		_scene->removeScenery(*it);
		delete *it;
	}
	_sceneries.clear();
	for (std::list<Sound::Sound*>::iterator it = _sounds.begin(); it != _sounds.end(); ++it)
		delete *it;
	_sounds.clear();
}

void GameController::update(void) {
    Vec2 time = _viewportPosition.getValue();
    //Log(time);
    _scene->setViewportPosition(time);
}

#pragma mark Getters

bool GameController::gameLaunched(void) const {
    return _gameLaunched;
}

uint16 GameController::getUdpSocketPort(void) const {
    return _udpPort;
}

Game* GameController::getGame(void) const {
    return _game;
}

#pragma mark Protocol commands

void GameController::receiveGraphicElements(Network::UdpPacket* packet) {

}

void GameController::receivePhysicElements(Network::UdpPacket* packet) {

}

void GameController::playSound(Network::UdpPacket* packet) {

}

void GameController::stopSound(Network::UdpPacket* packet) {

}

void GameController::updateTime(Network::UdpPacket* packet) {
  float32 time = 0, clock = 0;
  *packet >> time >> clock;
  _viewportPosition.setValue(Vec2(time, 0), clock);
}

void GameController::updateLife(Network::UdpPacket* packet) {

}

void GameController::updateScore(Network::UdpPacket* packet) {

}

void GameController::gameFinished(Network::UdpPacket* packet) {

}
