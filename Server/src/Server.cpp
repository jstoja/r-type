//
// Server.cpp for r-type in /home/michar_l//r-type/Server/src
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:20:57 2012 loick michard
//

#include "Game.h"
#include <Application.h>
#include <algorithm>

#include "Server.h"
#include "GameObject.h"
#include "Debug.h"

std::string	Server::_pluginDirectory = "Plugins";

Server::Server() {
	Application::getInstance().setRelativeResourcesPath("Resources");
  _tcpServer.setDelegate(this);
  if (_tcpServer.listen())
    Log("Server started on port : " << _tcpServer.getLocalPort());

    Game* game = new Game();
    game->setName("Game one");
    _games[game->getId()] = game;
    game->setNbSlots(4);
    game = new Game();
    game->setName("Game two");
    _games[game->getId()] = game;
    game = new Game();
    game->setName("Game three");
    _games[game->getId()] = game;
}

Server::~Server() {
  std::vector<Player*>::iterator it;
  for (it = _players.begin(); it != _players.end(); ++it)
    delete *it;
}

void Server::newConnection(Network::ASocket* socket) {
    _players.push_back(new Player(socket, this));
}

bool Server::canAddPlayer(std::string const& name) {
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it)
        if ((*it)->getName() == name)
            return false;
    return true;
}

bool Server::createGame(Game* game, Player* player) {
    uint32 id = game->getId();

    for (std::map<uint32, Game*>::iterator it = _games.begin(), end = _games.end();
         it != end; ++it) {
        if (it->second->getName() == game->getName())
            return false;
    }
    if (_games.find(id) == _games.end()) {
        _games[id] = game;
        game->join(player);
        return true;
    }
    return false;
}

int Server::joinGame(uint32 gameId, Player* player) {
    uint32 code;

    if (_games.find(gameId) != _games.end()) {
        if (_games[gameId]->canJoin(player)) {
            _games[gameId]->join(player);
            code = Network::TcpProxy::GameJoinSuccess;
        } else {
            code = Network::TcpProxy::GameJoinIsFull;
        }
    } else
        code = Network::TcpProxy::GameJoinInvalid;
    return code;
}

void  Server::playerReady(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->playerReady(player);
    }
}

void  Server::listPlayers(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->sendPlayerList(player);
    }
}

void  Server::sendResources(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        Network::TcpPacket *packet = new Network::TcpPacket();
        packet->setCode(Network::TcpProxy::GameResources);
        Network::Proxy<Network::TcpPacket>::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
        _games[gameId]->sendResources(*packet);
        player->sendPacket(toSend);
    }
}

void  Server::sendGameInfo(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->sendInfo(player);
    }
}

void Server::quitGame(Player* player) {
    Log("Player " << player->getName() << " leaved");
    for(std::map<uint32, Game*>::iterator it = _games.begin(); it != _games.end(); it++) {
        it->second->quit(player);
    }
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
    delete player;
}

void Server::gameStart(uint32 gameId) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->start();
    }
}

std::string Server::getName(void) const {
    return "Official R-Type server";
}

std::map<uint32, Game*> const& Server::getGames(void) const {
    return _games;
}

std::string const&	Server::getPluginDirectory() {
	return (_pluginDirectory);
}

void				Server::setPluginDirectory(std::string const& dir) {
	_pluginDirectory = dir;
}

int	Server::run() {
	Clock	clock;
	while (1) {
		clock.reset();
		for (std::map<uint32, Game*>::iterator it = _games.begin(); it != _games.end(); ++it)
			if (it->second->getState() == Game::Started)
				it->second->update();
		uint32 sleeping = (1000 / _sendFramerate) - clock.getEllapsedTime();
		if (sleeping > 0)
			Clock::sleep(sleeping);
	}
	return (0);
}
