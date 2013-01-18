//
// TcpServer.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Tue Dec 18 15:35:02 2012 loick michard
//

#include <iostream>
#include "OS.h"
#ifdef OS_WINDOWS
# include <winsock2.h>
#else
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
#endif
#include "TcpServer.h"

Network::TcpServer::TcpServer() : _socket(), _delegate(NULL) {
  _socket.setDelegate(this);
}

Network::TcpServer::~TcpServer() {

}

uint16 Network::TcpServer::getLocalPort() const {
  return _socket.getLocalPort();
}

bool Network::TcpServer::listen(const HostAddress& address, uint16 port) {
  return _socket.listen(address, port);
}

void Network::TcpServer::setDelegate(ITcpServerDelegate* delegate) {
  _delegate = delegate;
}

void Network::TcpServer::newConnection(Network::ASocket* socket) {
  if (_delegate)
    _delegate->newConnection(socket);
}
