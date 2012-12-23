//
// UdpPacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 10:45:12 2012 loick michard
//

#include <iostream>
#include "UdpPacket.h"

Network::UdpPacket::UdpPacket() {

}

Network::UdpPacket::~UdpPacket() {

}

void Network::UdpPacket::read(ASocket* socket) {
  if (_data.getSize() == 0) {
    socket->read(_data, false);
  }
}

void Network::UdpPacket::update() {
}

bool Network::UdpPacket::isComplete() const {
  if (_data.getSize() == 0)
    return false;
  return true;
}
