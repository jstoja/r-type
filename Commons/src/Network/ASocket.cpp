//
// ASocket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Dec 18 21:53:11 2012 loick michard
//

#include "ASocket.h"
#include "NetworkManager.h"
#include "Debug.h"


Network::ASocket::ASocket() : _reading(false), _listening(false), _writing(false), _delegate(NULL) {
  NetworkManager::getInstance().registerSocket(this);
}

Network::ASocket::~ASocket() {
  
}

bool Network::ASocket::isListening() const {
  return _listening;
}

bool Network::ASocket::isReading() const {
  return _reading;
}

bool Network::ASocket::isWriting() const {
  return _writing;
}

void Network::ASocket::setDelegate(ISocketDelegate* delegate) {
  _delegate = delegate;
}
