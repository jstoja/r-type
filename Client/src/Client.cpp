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
#include "Graphic/TextureManager.h"
#include "Application.h"

#include "Graphic/Image.h"

Client::Client(void) :
_close(false), _scene(), _framerateLimit(30), _time(), _ui(),
_tcpSocket(NULL), _proxy(NULL),
_commands(), _login(""), _userId(0), _currentGame(NULL),
_gameController(NULL) {
    
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
    
    // Create the event listener to get the close event
    _eventListener = new Event::Listener(Event::Close, this);
    Event::Manager::getInstance().addEventListener(_eventListener);
    
    // Create the ui
    _ui = new UserInterface(this);

    mainLoop();
}

Client::~Client(void) {
    delete _tcpSocket;
    delete _proxy;
    Event::Manager::getInstance().removeEventListener(_eventListener);
    delete _eventListener;
}

#pragma mark Application main functions

void Client::mainLoop(void) {
#ifndef OS_IOS
    while (!_close) {
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
    if (_gameController && _gameController->gameLaunched())
        _gameController->update();
    else
        _ui->update();
    Graphic::TextureManager::getInstance().update();
}

void Client::render(void) {
    Graphic::Renderer::getInstance().render();
}

uint32 Client::getFramerateLimit(void) const {
    return _framerateLimit;
}

#pragma mark Event Listener delegate methods

void Client::processEvent(Event::Event const& event) {
    if (event.type & Event::Close) {
        _close = true;
    }
}

#pragma mark User interface delegate methods

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
	if (_currentGame && _gameController) {
		Network::TcpPacket* packet = new Network::TcpPacket();
		packet->setCode(Network::TcpProxy::PlayerReady);
        Log("LOCAL PORT" << (uint16)_gameController->getUdpSocketPort());
        *packet << _currentGame->getId() << (uint16)_gameController->getUdpSocketPort();
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

#pragma mark Network proxy delegate methods

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
}

void Client::connectionClosed(Network::Proxy<Network::TcpPacket>* proxy) {
    _ui->goToMenu("Login");
    _currentGame = NULL;
    Log("Connection closed");
}

void Client::packetInProgress(uint32 code, float32 progress) {
	if (code == Network::TcpProxy::GameResources) {
		_ui->setResourceProgress(progress);
	}
}

#pragma mark Protocol commands
	
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
        _initGame(game);
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
        _initGame(_currentGame);        
	} else if ((packet->getCode() & 0xff) == 1) {
        Log("Cannot join game: game is full");
    } else if ((packet->getCode() & 0xff) == 2) {
        Log("Cannot join game: invalid game");
    } else {
        Log("Cannot join game: invalid error");
    }
}

void Client::receiveResources(Network::TcpPacket* packet) {
    if (_gameController)
        _gameController->receiveResources(packet);
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
			return ;
		}
}

void Client::startGame(Network::TcpPacket* packet) {
    uint32 gameId = 0;
    uint16 serverUdpPort = 0;
    *packet >> gameId >> serverUdpPort;
    Log("UdpPort " << serverUdpPort);
    if (_gameController && _gameController->getGame()->getId() == gameId) {
        _ui->setVisible(false);
		_gameController->launchGame(_tcpSocket->getRemoteAddress(), serverUdpPort);
    }
}

#pragma mark Socket delegate

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

#pragma mark Game functions

void Client::_initGame(Game* game) {
    _currentGame = game;
    _ui->setGameName(game->getName());
    _ui->setCurrentGame(_currentGame);
    _gameController = new GameController(_currentGame, &_scene);
    _ui->goToMenu("GameJoin");
}

void Client::_clearGame() {
    if (_gameController)
        _gameController->clearGame();
}
