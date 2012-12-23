//
// Server.cpp for r-type in /home/michar_l//r-type/Server/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 09:20:57 2012 loick michard
//

#include "Server.h"

Server::Server() {
  _tcpServer.setDelegate(this);
  if (_tcpServer.listen())
    std::cout << "Server started on port : " << _tcpServer.getLocalPort() << std::endl;
}

Server::~Server() {
  std::vector<Client*>::iterator it;
  for (it = _clients.begin(); it != _clients.end(); ++it)
    delete *it;
}

void Server::newConnection(Network::ASocket* socket) {
  _clients.push_back(new Client(socket));
}
