//
// Client.cpp for r-type in /home/michar_l//r-type/Server/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 09:35:41 2012 loick michard
//

#include <iostream>
#include "Client.h"

Client::Client(Network::ASocket* socket) : _socket(socket) {
  std::cout << "New Client" << std::endl;
}

Client::~Client() {
  delete _socket;
}
