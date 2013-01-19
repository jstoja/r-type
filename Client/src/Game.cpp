//
// Game.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 10:36:08 2013 Samuel Olivier
//

#include "Game.h"

Game::Game(uint32 id) : Object(id), _nbPlayer(0), _nbSlot(0) {
}

Game::~Game() {
	_clear();
}

void	Game::setName(std::string const& name) {
	_name = name;
}

std::string const&	Game::getName() const {
	return (_name);
}

void	Game::setNbPlayer(uint32 nbPlayer) {
	_nbPlayer = nbPlayer;
}

uint32	Game::getNbPlayer() const {
	return (_nbPlayer);
}

void	Game::setNbSlot(uint32 nbSlot) {
	_nbSlot = nbSlot;
}

uint32	Game::getNbSlot() const {
	return (_nbSlot);
}

void	Game::addPlayer(Player* player) {
	_players.push_back(player);
	_nbPlayer = _players.size();
}

void	Game::addPlayer(Network::TcpPacket& packet) {
	_players.push_back(Player::newPlayer(packet));
	_nbPlayer = _players.size();
}

std::list<Player*> const& Game::getPlayers() const {
	return (_players);
}

void	Game::setPlayers(std::list<Player*> const& players) {
	_clear();
	_players = players;
	_nbPlayer = _players.size();
}

void	Game::setPlayers(Network::TcpPacket& packet) {
	uint32 size;

	_clear();
	packet >> size;
	for (uint32 i = 0; i < size; ++i) {
		Player* player = Player::newPlayer(packet);
		_players.push_back(player);
	}
	_nbPlayer = _players.size();
}

void	Game::_clear() {
	for (std::list<Player*>::iterator it = _players.begin(); it != _players.end(); ++it)
		delete *it;
	_players.clear();
	_nbPlayer = 0;
}

void	Game::setPlayerReady(uint32 playerId, bool value) {
	for (std::list<Player*>::iterator it = _players.begin(); it != _players.end(); ++it)
		if ((*it)->getId() == playerId)
			(*it)->setIsReady(value);
}

Game*	Game::newGame(Network::TcpPacket& packet) {
	uint32	id, nbPlayer, nbSlot;
	std::string name;
	Game*	res;

	packet >> id >> name >> nbPlayer >> nbSlot;
	res = new Game(id);
	res->setName(name);
	res->setNbPlayer(nbPlayer);
	res->setNbSlot(nbSlot);
	return (res);
}
