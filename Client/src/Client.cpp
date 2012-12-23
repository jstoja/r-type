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
