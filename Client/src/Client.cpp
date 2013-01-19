//
// Client.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 13:59:18 2012 loick michard
//

#include "Client.h"

#include "Graphic/Renderer.h"
#include "Event/Manager.h"
#include "Application.h"
#include "ObjectManager.h"

#include "Graphic/Image.h"

Client::Client(void) :
_scene(), _framerateLimit(30), _time(), _ui(), _tcpSocket(NULL), _proxy(NULL),
_commands(), _login(""), _userId(0), _currentGame(NULL) {
    
    _commands[Network::TcpProxy::AuthenficitationConnectionSuccess] = &Client::connectionResponse;
    _commands[Network::TcpProxy::InformationsGameGeneralResponse] = &Client::receiveGeneralInformations;
    _commands[Network::TcpProxy::InformationsGameListResponse] = &Client::receiveGameList;
    _commands[Network::TcpProxy::GameCreatedSuccess] = &Client::gameCreatedResponse;
    _commands[Network::TcpProxy::GameJoinSuccess] = &Client::gameJoinResponse;
	_commands[Network::TcpProxy::GameResources] = &Client::receiveResources;
	_commands[Network::TcpProxy::GamePlayerList] = &Client::receivePlayerList;
	_commands[Network::TcpProxy::GameNewPlayer] = &Client::receiveNewPlayer;
	_commands[Network::TcpProxy::GamePlayerReady] = &Client::receivePlayerReady;
    _commands[Network::TcpProxy::GameStart] = &Client::startGame;
    Graphic::Renderer::getInstance().init();
    Graphic::Renderer::getInstance().setScene(&_scene);
    
    // Adapt the scene viewport to the window aspect
    Vec2 viewport = _scene.getViewport();
    Vec2 screen = Graphic::Renderer::getInstance().getViewportSize();
    
    viewport.x = viewport.y * (screen.x / screen.y);
    _scene.setViewport(viewport);
    
    // Create the ui
    _ui = new UserInterface(this);

    mainLoop();
}

Client::~Client(void) {
    delete _tcpSocket;
    delete _proxy;
}

void Client::mainLoop(void) {
#ifndef OS_IOS
    while (true) {
        Clock frameClock;
        
        update();
        render();
        
        // Framerate limitation
        uint64 frameTime = 1000 / _framerateLimit;
        uint64 ellapsedTime = frameClock.getEllapsedTime();
        if (ellapsedTime < frameTime) {
            Clock::sleep(frameTime - ellapsedTime);
        }
        frameClock.reset();
    }
#endif
}

void Client::update(void) {
    Event::Manager::getInstance().processEvents();
    _ui->update();
}

void Client::render(void) {
    Graphic::Renderer::getInstance().render();
}

uint32 Client::getFramerateLimit(void) const {
    return _framerateLimit;
}

Graphic::Scene* Client::getScene(void) {
    return &_scene;
}

void Client::loginCompleted(std::string const& login, std::string const& ipAdress,
                            std::string const& port) {
    delete _tcpSocket;
    delete _proxy;
    _proxy = NULL;
    _login = login;
    _tcpSocket = new Network::TcpSocket(this);
	_tcpSocket->connect(ipAdress, std::atoi(port.c_str()));
    _ui->presentMessage("Connecting...");
}

void Client::newGameCompleted(std::string const& name, uint32 nbPlayers) {
    Network::TcpPacket* packet = new Network::TcpPacket();
    packet->setCode(Network::TcpProxy::GameCreate);
    *packet << name;
    *packet << nbPlayers;
    _proxy->sendPacket(packet);
    _ui->presentMessage("Creating game...");
}

void Client::gameSelected(uint32 gameIndex) {
    if (gameIndex < _games.size()) {
        std::list<Game*>::iterator it = _games.begin();
        std::advance(it, gameIndex);
        Game* game = *it;
        
        Network::TcpPacket* packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::GameJoin);
        *packet << game->getId();
        _proxy->sendPacket(packet);

        Log("Joining game " << game->getName());
    } else {
        Log("Tried to join game with invalid index");
    }
}

void Client::playerReady() {
	if (_currentGame) {
		Network::TcpPacket* packet = new Network::TcpPacket();
		packet->setCode(Network::TcpProxy::PlayerReady);
        *packet << _currentGame->getId();
        _proxy->sendPacket(packet);
		_currentGame->setPlayerReady(_userId, true);
		_ui->setCurrentGame(_currentGame);
    }
}

void Client::leavedGameList(void) {
    _ui->goToMenu("Login");
    delete _proxy;
    _proxy = NULL;
    delete _tcpSocket;
    _tcpSocket = NULL;
}

void Client::leavedGame(void) {
    // Inform the server we leaved the game
    Network::TcpPacket* packet = new Network::TcpPacket();
    packet->setCode(Network::TcpProxy::GameQuit);
    *packet << _currentGame->getId();
    _proxy->sendPacket(packet);
    // Re-request game list
    packet = new Network::TcpPacket();
    packet->setCode(Network::TcpProxy::InformationsGameList);
    _proxy->sendPacket(packet);
    
    _currentGame = NULL;
    _ui->goToMenu("GameList");
}

void Client::packetReceived(Network::TcpPacket* packet) {
    uint32 code, size;
    
    *packet >> code >> size;
    std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
    if (it != _commands.end())
        (this->*(it->second))(packet);
    else
        Log("Received unknown command 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
    delete packet;
}


void Client::packetSent(Network::TcpPacket const* packet) {
    Log("Packet sent");
}

void Client::packetInProgress(uint32 code, float32 progress) {
	Log(code << progress);
}
	
void Client::connectionResponse(Network::TcpPacket* packet) {
    if ((packet->getCode() & 0xFF) == 1) {
        Log("Connection error: incorrect login");
        _ui->hideMessage();
        _ui->goToMenu("Login");
    } else {
        uint32 id;
        *packet >> id;
        
        _userId = id;
        
        // Request server infos and games list
        Network::TcpPacket* packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::InformationsGeneral);
        _proxy->sendPacket(packet);
        packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::InformationsGameList);
        _proxy->sendPacket(packet);
        
        _ui->hideMessage();
        _ui->goToMenu("GameList");
    }
}

void Client::receiveGeneralInformations(Network::TcpPacket* packet) {
    std::string serverName;
    *packet >> serverName;
    _ui->setServerName(serverName);
}

void Client::receiveGameList(Network::TcpPacket* packet) {
    uint32 nbGames = 0;
    *packet >> nbGames;
    std::list<Game*> games;
    for (uint32 i = 0; i < nbGames; ++i) {
        Game* game = Game::newGame(*packet);
		if (_currentGame && _currentGame->getId() == game->getId())
			_currentGame = game;
        games.push_back(game);
    }
    _ui->setGameList(games);
    for (std::list<Game*>::iterator it = _games.begin(), end = _games.end();
         it != end; ++it) {
        delete *it;
    }
    _games = games;
}

void Client::gameCreatedResponse(Network::TcpPacket* packet) {
    _ui->hideMessage();    
    if ((packet->getCode() & 0xff) == 1) {
        _ui->goToMenu("NewGame");
        Log("Game not created");
    } else {
        Game* game = Game::newGame(*packet);
        _games.push_back(game);
        _ui->setGameList(_games);
        _currentGame = game;
        _ui->setGameName(game->getName());
        _ui->setCurrentGame(_currentGame);
        _ui->goToMenu("GameJoin");
        Log("Created game: " << game->getName() << ", id: " << game->getId());
    }
}

void Client::gameJoinResponse(Network::TcpPacket* packet) {
    if ((packet->getCode() & 0xff) == 0) {        
		uint32 id;
		*packet >> id;
		_currentGame = NULL;
		for (std::list<Game*>::iterator it = _games.begin(); it != _games.end(); ++it)
			if ((*it)->getId() == id) {
				_currentGame = *it;
				break;
			}
		if (_currentGame == NULL) {
	        Log("Cannot join game: unknown Game Id on client Side");
			return ;
		}
		_ui->setGameName(_currentGame->getName());
		_ui->setCurrentGame(_currentGame);
        _ui->goToMenu("GameJoin");        
	} else if ((packet->getCode() & 0xff) == 1) {
        Log("Cannot join game: game is full");
    } else if ((packet->getCode() & 0xff) == 2) {
        Log("Cannot join game: invalid game");
    } else {
        Log("Cannot join game: invalid error");
    }
}

void Client::receiveResources(Network::TcpPacket* packet) {
    uint32 nb;
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Resource* resource = createResource(*packet);
		if (resource)
			_gameResources.push_back(resource);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Texture* texture = createTexture(*packet);
		if (texture)
			_gameTextures.push_back(texture);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Sprite* sprite = createSprite(*packet);
		if (sprite)
			_gameSprites.push_back(sprite);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Element* element = createGraphicElement(*packet);
		if (element)
			_gameElements.push_back(element);
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Graphic::Scenery* scenery = createScenery(*packet);
		if (scenery) {
			_gameSceneries.push_back(scenery);
		}
    }
    *packet >> nb;
    for (uint32 i = 0; i < nb; ++i) {
		Sound::Sound* sound = createSound(*packet);
		if (sound)
			_gameSounds.push_back(sound);
    }
	_ui->goToMenu("GamePrepare");
}

void Client::receivePlayerList(Network::TcpPacket* packet) {
	uint32 id;
	*packet >> id;
	for (std::list<Game*>::iterator it = _games.begin(); it != _games.end(); ++it)
		if ((*it)->getId() == id) {
			(*it)->setPlayers(*packet);
			if (_currentGame)
				_ui->setCurrentGame(_currentGame);
			return ;
		}
}

void Client::receiveNewPlayer(Network::TcpPacket* packet) {
	uint32 id;
	*packet >> id;
	for (std::list<Game*>::iterator it = _games.begin(); it != _games.end(); ++it)
		if ((*it)->getId() == id) {
			(*it)->addPlayer(*packet);
			if (_currentGame)
				_ui->setCurrentGame(_currentGame);
			return ;
		}
}

void Client::receivePlayerReady(Network::TcpPacket* packet) {
	uint32 id;
	*packet >> id;
	for (std::list<Game*>::iterator it = _games.begin(); it != _games.end(); ++it)
		if ((*it)->getId() == id) {
			*packet >> id;
			(*it)->setPlayerReady(id, true);
			if (_currentGame)
				_ui->setCurrentGame(_currentGame);
			return ;
		}
}

void Client::startGame(Network::TcpPacket* packet) {
	_ui->setVisible(false);
	_initGame();
}

void Client::connectionClosed(Network::Proxy<Network::TcpPacket>* packet) {
    Log("Connection closed");
}

void Client::connectionFinished(Network::ASocket* socket, bool success) {
    if (success) {
        Log("Connected to server");
        _proxy = new Network::Proxy<Network::TcpPacket>(_tcpSocket, this);
        Network::TcpPacket* packet = new Network::TcpPacket();
        packet->setCode(Network::Proxy<Network::TcpPacket>::AuthenficitationConnection);
        *packet << _login;
        _proxy->sendPacket(packet);
    }
    else {
        _ui->hideMessage();
        _ui->goToMenu("Login");
        Log("Connection failed");
    }
}

Resource*		Client::createResource(Network::TcpPacket& packet) {
	uint32		id;
	Resource	*res;
	ByteArray	data;

	packet >> id >> data;
	res = new Resource(id);
	res->setData(data);
	return (res);
}

Graphic::Texture*		Client::createTexture(Network::TcpPacket& packet) {
	uint32		id, resourceId;

	packet >> id >> resourceId;
	Resource *resource = dynamic_cast<Resource*>(ObjectManager::getInstance().getObject(resourceId));
	if (resource)
		return (new Graphic::Texture(id, resource));
	return (NULL);
}

Graphic::Sprite*		Client::createSprite(Network::TcpPacket& packet) {
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

Graphic::Element*	Client::createGraphicElement(Network::TcpPacket& packet) {
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

Graphic::Scenery*	Client::createScenery(Network::TcpPacket& packet) {
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

Sound::Sound*		Client::createSound(Network::TcpPacket& packet) {
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

void Client::_initGame() {
	for (std::list<Graphic::Element*>::iterator it = _gameElements.begin(); it != _gameElements.end(); ++it) {
		if (*it) {
			(*it)->setVisible(true);
			_scene.addElement(*it);
		}
	}
	for (std::list<Graphic::Scenery*>::iterator it = _gameSceneries.begin(); it != _gameSceneries.end(); ++it) {
		if (*it) {
			_scene.addScenery(*it);
		}
	}
}

void Client::_clearGame() {
	for (std::list<Resource*>::iterator it = _gameResources.begin(); it != _gameResources.end(); ++it)
		delete *it;
	_gameResources.clear();
	for (std::list<Graphic::Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		delete *it;
	_gameTextures.clear();
	for (std::list<Graphic::Sprite*>::iterator it = _gameSprites.begin(); it != _gameSprites.end(); ++it)
		delete *it;
	_gameSprites.clear();
	for (std::list<Graphic::Element*>::iterator it = _gameElements.begin(); it != _gameElements.end(); ++it) {
		_scene.removeElement(*it);
		delete *it;
	}
	_gameElements.clear();
	for (std::list<Graphic::Scenery*>::iterator it = _gameSceneries.begin(); it != _gameSceneries.end(); ++it) {
		_scene.removeScenery(*it);
		delete *it;
	}
	_gameSceneries.clear();
	for (std::list<Sound::Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		delete *it;
	_gameSounds.clear();
}