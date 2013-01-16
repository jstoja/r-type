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

#include "Server.h"
#include "GameObject.h"

std::string	Server::_pluginDirectory = "Plugins";

Server::Server() {
	Application::getInstance().setRelativeResourcesPath("Resources");
  _tcpServer.setDelegate(this);
  if (_tcpServer.listen())
    std::cout << "Server started on port : " << _tcpServer.getLocalPort() << std::endl;
}

Server::~Server() {
  std::vector<Player*>::iterator it;
  for (it = _players.begin(); it != _players.end(); ++it)
    delete *it;
}

void Server::newConnection(Network::ASocket* socket) {
  _players.push_back(new Player(socket, this));
}


bool Server::createGame(Game* game, Player* player) {
    uint32 id = game->getId();

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
        if (_games[gameId]->canJoin()) {
            _games[gameId]->join(player);
            code = 0;
        } else {
            code = 1;
        }
    }
    code = 2;
    return code;
}

void  Server::playerReady(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->playerReady(player);
    }
}

void  Server::sendResources(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {

        Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
        toSend.packet->setCode(0x01020200);
        _games[gameId]->sendResources(*toSend.packet);
        player->sendPacket(toSend);
    }
}

void Server::quitGame(uint32 gameId, Player* player) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->quit(player);
    }
}

void Server::gameStart(uint32 gameId) {
    if (_games.find(gameId) != _games.end()) {
        _games[gameId]->start();
    }
}

std::map<uint32, Game*> const& Server::getGames(void) {
    return _games;
}

std::string const&	Server::getPluginDirectory() {
	return (_pluginDirectory);
}

void				Server::setPluginDirectory(std::string const& dir) {
	_pluginDirectory = dir;
}
