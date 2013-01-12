//
// Player.cpp for r-type in /home/michar_l//r-type/Server/src
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:35:41 2012 loick michard
//

#include <iostream>
#include "Player.h"

Player::Player(Network::ASocket* socket, IServerDelegate* server) : _socket(socket), _proxy(socket, this), _server(server) {
  std::cout << "New Player" << std::endl;

  _commands[0x00000000] = &Player::connection;
  _commands[0x00000200] = &Player::joinGame;
  // _commands[0x00000210] = &Player::quitGame;
  _commands[0x00000220] = &Player::createGame;
  // _commands[0x00000230] = &Player::readyToStart;
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


void Player::createGame(Network::TcpPacket* packet) {
    Game *game = new Game(packet);
    bool gameCreated = _server->createGame(game, this);

    if (gameCreated == false) {
        delete game;
    }

    Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
    toSend.packet->setCode(0x1230);
    *toSend.packet << (uint32)(gameCreated ? 3 : 1);
    _proxy.sendPacket(toSend);
 }


void Player::joinGame(Network::TcpPacket* packet) {
    uint32 id;
    int code;

    *packet >> id;
    code = _server->joinGame(id, this);

    Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
    toSend.packet->setCode(0x1200);
    *toSend.packet << (uint32)code;
    _proxy.sendPacket(toSend);
 }

void Player::quitGame(Network::TcpPacket* packet) {
    uint32 id;
    int code;

    *packet >> id;
    _server->quitGame(id, this);
 }