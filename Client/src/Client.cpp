//
// Client.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 13:59:18 2012 loick michard
//

#include "Client.h"

Client::Client(const std::string& ip, uint16 port) : _proxy(NULL) {

  _commands[0x01000000] = &Client::connectionSuccess;

  if (_tcpSocket.connect(ip, port)) {
    _proxy = new Network::Proxy<Network::TcpPacket>(&_tcpSocket, this);
  } else {
    std::cout << "Couln't connect to server" << std::endl;
  }

  this->connection("USERNAME");
}

Client::~Client() {

}

void Client::newPacket(Network::TcpPacket* packet) {
  uint32 code, size;

  *packet >> code >> size;
  std::cout << code << " -> Size : " << size << std::endl;
  std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
  if (it != _commands.end())
    (this->*(it->second))(packet);
  delete packet;
}

void Client::packetWrited(Network::TcpPacket* packet) {
  delete packet;
}

void Client::connection(const std::string& name) {
  Network::Proxy<Network::TcpPacket>::ToSend toSend(new Network::TcpPacket(), Network::HostAddress::AnyAddress, 0);
  toSend.packet->setCode(0x00000000);
  *toSend.packet << name;
  _proxy->sendPacket(toSend);
}

void Client::connectionSuccess(Network::TcpPacket* packet) {
  uint32 id;

  *packet >> id;

  std::cout << "Connexion success ! My id is " << id << std::endl;
}

void Client::welcomeCompleted(void) {

}
