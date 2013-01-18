//
// Game.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 10:36:08 2013 Samuel Olivier
//

#include "Game.h"

Game::Game(uint32 id) {

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