//
// TcpPacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 10:45:12 2012 loick michard
//

#include <iostream>
#include "TcpPacket.h"
#include "Debug.h"

Network::TcpPacket::TcpPacket() : APacket(), _state(Empty) {

}

Network::TcpPacket::~TcpPacket() {

}

void Network::TcpPacket::read(ASocket* socket) {    
  if (_data.getSize() == 0 && _state == Empty) {
    _data.resize(8);
    socket->read(_data, true);
  }
  else if (_state == Header) {
    _data.resize(_size);
    socket->read(_data, true, 8);
  }
}

void Network::TcpPacket::update() {
  if (_data.getSize() == 8) {
    _state = Header;
    uint32 size = *((int*)(&((char*)_data)[4]));
    if (size == 0)
      _state = Complete;
    _size = 8 + size;
  }
  else if (_data.getSize() > 8) {
    _state = Complete;
  }
}

bool Network::TcpPacket::isComplete() const {
  return (_state == Complete);
}

void Network::TcpPacket::setCode(uint32 code) {
  if (_data.getSize() < 8)
    _data.resize(8);

  *((int*)(&((char*)_data)[0])) = code;
  *((int*)(&((char*)_data)[4])) = 0;
}

uint32 Network::TcpPacket::getCode() {
  if (_data.getSize() >= 4)
    return *((int*)(&((char*)_data)[0]));
  return 0;
}

void Network::TcpPacket::updateData() {
    Log("Updated");
    if (_data.getSize() >= 8)
        *((int*)(&((char*)_data)[4])) = _size;
}
