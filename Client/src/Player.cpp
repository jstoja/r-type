//
// Player.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 10:36:08 2013 Samuel Olivier
//

#include "Player.h"

Player::Player(uint32 id) : Object(id), _isReady(false) {
}

void	Player::setName(std::string const& name) {
	_name = name;
}

std::string const&	Player::getName() const {
	return (_name);
}

void	Player::setIsReady(bool isReady) {
	_isReady = isReady;
}

bool	Player::isReady() const {
	return (_isReady);
}

Player*	Player::newPlayer(Network::TcpPacket& packet) {
	uint32	id;
	std::string name;
    char isReady;
	Player*	res;

	packet >> id >> name >> isReady;
	res = new Player(id);
	res->setName(name);
    res->setIsReady(isReady);
	return (res);
}