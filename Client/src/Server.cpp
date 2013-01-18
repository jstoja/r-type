//
//  Server.cpp
//  R-Type
//
//  Created by Gael du Plessix on 18/01/13.
//
//

#include "Server.h"

Server::Server(void) {
    
}

Server::~Server(void) {
    
}

Server* Server::newServer(Network::TcpPacket& packet) {
    Server* server = new Server();
    packet >> server->_name;
    return server;
}

void Server::clearGames(void) {
    for (std::vector<Game*>::iterator it = _games.begin(), end = _games.end();
         it != end; ++it) {
        delete *it;
    }
    _games.clear();
}

void Server::readGameList(Network::TcpPacket& packet) {
    uint32 nbGames = 0;
    packet >> nbGames;
    clearGames();
    _games.resize(nbGames);
    for (uint32 i = 0; i < nbGames; ++i) {
        _games[i] = Game::newGame(packet);
    }
}