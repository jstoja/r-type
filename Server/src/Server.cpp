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
    game->setNbSlots(1);
    game = new Game();
    game->setName("Game two");
    _games[game->getId()] = game;
    game = new Game();
    game->setName("Game three");
    _games[game->getId()] = game;

    _gameStateMutex = new Threading::Mutex();
}

Server::~Server() {
  std::vector<Player*>::iterator it;
  for (it = _players.begin(); it != _players.end(); ++it)
    delete *it;
}

void Server::newConnection(Network::TcpSocket* socket) {
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
        game->setReferee(player);
        game->join(player);
        informNewGame(game, player);
        return true;
    }
    return false;
}

int Server::joinGame(uint32 gameId, Player* player) {
    uint32 code;

    if (_games.find(gameId) != _games.end()) {
        if (_games[gameId]->canJoin(player)) {
            _games[gameId]->join(player);
            informGameJoin(player, _games[gameId]);
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

void Server::quitServer(Player* player) {
    Log("Player " << player->getName() << " leaved server");
    for(std::map<uint32, Game*>::iterator it = _games.begin(); it != _games.end(); it++) {
        if (it->second->hasPlayer(player)) {
            // UGLY DIRTY SHIT

            quitGame(player, it->first);
            break;

            // UGLY DIRTY SHIT
        }
    }

    //_players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
    //delete player;
}

void Server::quitGame(Player *player, uint32 gameId) {
    bool     noPlayer;
    std::map<uint32, Game*>::iterator it = _games.find(gameId);

    if (it != _games.end()) {
        // Remove player from game
        Game* game = it->second;
        bool stopGame = game->quit(player);
        Log("Player " << player->getName() << " leaved game " << game->getName());
        Log("Referee is : " << game->getReferee()->getName());

        if (stopGame) {
            Threading::MutexLocker locker(_gameStateMutex);
            Log("Referee logged out. Stopping " << game->getName()) << " (NOT IMPLEMENTED YET)";

            std::vector<Player*>  playersToRemove =  game->getPlayers();

            for (int i = 0; i < playersToRemove.size(); ++i) {
                _players.erase(std::remove(_players.begin(), _players.end(), playersToRemove[i]), _players.end());
                delete playersToRemove[i];
            }

            _games.erase(it);
            delete game;
        } else {
            informGameQuit(player, game);
        }
    }
}

void Server::informGameQuit(Player* player, Game* game) {
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        if (*it != player) {
            if (game->hasPlayer(*it))
                game->sendPlayerList(*it);
            else {
                (*it)->sendGamesList();
            }
        }
    }
}

void Server::informGameJoin(Player* player, Game* game) {
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        if (*it != player) {
            if (game->hasPlayer(*it)) {
                Network::TcpPacket *packet = new Network::TcpPacket();
                packet->setCode(Network::TcpProxy::GameNewPlayer);
                *packet << game->getId() << *player;
                Network::TcpProxy::ToSend toSend(packet, Network::HostAddress::AnyAddress, 0);
                (*it)->sendPacket(toSend);
            }
            else {
                (*it)->sendGamesList();
            }
        }
    }
}

void Server::informNewGame(Game* game, Player* player) {
    for (std::vector<Player*>::iterator it = _players.begin(), end = _players.end();
         it != end; ++it) {
        if (*it != player) {
            (*it)->sendGamesList();
        }
    }
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
	while (true) {

        _gameStateMutex->lock();
		for (std::map<uint32, Game*>::iterator it = _games.begin(); it != _games.end(); ++it) {
			if (it->second->getState() == Game::Started)
				it->second->update();
        }
        _gameStateMutex->unlock();

        int32 sleeping = (1000 / _sendFramerate) - clock.getEllapsedTime();
		if (sleeping > 0)
			Clock::sleep(sleeping);
        clock.reset();

	}
	return (0);
}
