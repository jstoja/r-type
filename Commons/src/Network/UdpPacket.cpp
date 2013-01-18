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

void Network::UdpPacket::setCode(uint32 code) {
  if (_data.getSize() < 8)
    _data.resize(8);
  *((int*)(&((char*)_data)[0])) = code;
  *((int*)(&((char*)_data)[4])) = _size;
}

uint32 Network::UdpPacket::getCode() {
  if (_data.getSize() >= 4)
    return *((int*)(&((char*)_data)[0]));
  return 0;
}

bool	Network::UdpPacket::getHeaderInfos(ByteArray const& data, uint32& code) {
	code = 0;
	return (false);
}
