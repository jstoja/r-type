//
// Player.cpp for r-type in /home/michar_l//r-type/Server/src
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:35:41 2012 loick michard
//

#include <iostream>
#include "Game.h"
#include "Player.h"

Player::Player(Network::ASocket* socket, IServerDelegate* server) : _isReady(false), _socket(socket), _proxy(socket, this), _server(server) {
  std::cout << "New Player" << std::endl;

  _commands[0x00000000] = &Player::connection;
  _commands[0x00010000] = &Player::listGame;
  _commands[0x00020000] = &Player::joinGame;
  _commands[0x00020100] = &Player::quitGame;
  _commands[0x00020200] = &Player::createGame;
  _commands[0x00020300] = &Player::readyToStart;
}

Player::~Player() {
  delete _socket;
}

void Player::newPacket(Network::TcpPacket* packet) {
  uint32 code, size;

  *packet >> code >> size;
  std::cout << code << " -> Size : " << size << std::endl;
  std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
  if (it != _commands.end())
    (this->*(it->second))(packet);
  delete packet;
}

void Player::packetWrited(Network::TcpPacket* packet) {
  delete packet;
}

void Player::connection(Network::TcpPacket* packet) {
  std::string login;

  *packet >> login;
  std::cout << "Connection with login " << login << std::endl;

  Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
  toSend.packet->setCode(0x01000000);
  *toSend.packet << (uint32)42;
  _proxy.sendPacket(toSend);
}

void  Player::sendPacket(Network::Proxy<Network::TcpPacket>::ToSend const& toSend) {
    _proxy.sendPacket(toSend);
}

void Player::createGame(Network::TcpPacket* packet) {
    Game *game = new Game(packet);
    bool gameCreated = _server->createGame(game, this);

    if (gameCreated == false) {
        delete game;
    }

    Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
    toSend.packet->setCode(0x01020300 + (gameCreated ? 3 : 1));
    *toSend.packet << *game;
    _proxy.sendPacket(toSend);
 }

void Player::joinGame(Network::TcpPacket* packet) {
    uint32 id;

    *packet >> id;
    int code = 0x01020000 + _server->joinGame(id, this);

    Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
    toSend.packet->setCode(code);
    *toSend.packet << id;
    _proxy.sendPacket(toSend);
    _server->sendResources(id, this);
 }

void Player::quitGame(Network::TcpPacket* packet) {
    uint32 id;

    *packet >> id;
    _isReady = false;
    _server->quitGame(id, this);
 }


void Player::listGame(Network::TcpPacket* packet) {
    std::map<uint32, Game*> games = _server->getGames();

    std::list<Game*> newGamesList;
    for (int i=0; i<games.size(); i++) {
        newGamesList.push_back(games[i]);
    }

    Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
    toSend.packet->setCode(0x01010100);
    *toSend.packet << newGamesList;
    _proxy.sendPacket(toSend);
}

void Player::readyToStart(Network::TcpPacket* packet) {
    uint32 gameId;

    *packet >> gameId;
    _isReady = true;
    _server->playerReady(gameId, this);
}


Network::APacket&       operator<<(Network::APacket& packet, Player const& player) {
    packet << player.getId();
    return packet;
}