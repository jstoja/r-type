//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#include <algorithm>
#include "Network/TcpServer.h"
#include "Game.h"

Game::Game(Network::TcpPacket* packet) {
    *packet >> _name;
    *packet >> (unint32)_nbSlots;
}

Game::~Game() {}

std::string const&     Game::getName(void) {
    return _name;
}

bool     Game::canJoin(void) {
    return _nbSlots > _players.size();
}

void     Game::join(Player* player) {
   if (canJoin()) {
    _players.push_back(player);
   }
}

void     Game::quit(Player* player) {
    _players = std::remove(_players->begin(), _players->end(), player);
}