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

Player::Player(Network::ASocket* socket) : _socket(socket), _proxy(socket, this) {
  std::cout << "New Player" << std::endl;

  _commands[0x00000000] = &Player::connection;
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
