//
// UdpPacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 10:45:12 2012 loick michard
//

#include <iostream>
#include "UUIDGenerator.h"
#include "UdpPacket.h"

Network::UdpPacket::UdpPacket() : 
APacket(), _hostAddress(Network::HostAddress::AnyAddress) {
  _port = 0;
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

void Network::UdpPacket::setId(uint32 code) {
  if (_data.getSize() < 8)
    _data.resize(8);
  *((int*)(&((char*)_data)[5])) = code;
}

void Network::UdpPacket::generateId(void) {
    setId(UUIDGenerator::getInstance().getUUID());
}

uint32 Network::UdpPacket::getId() {
  if (_data.getSize() >= 8)
    return *((int*)(&((char*)_data)[5]));
  return 0;
}

void Network::UdpPacket::setCode(uint32 code) {
  if (_data.getSize() < 4)
    _data.resize(4);
  *((int*)(&((char*)_data)[0])) = code;
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

Network::HostAddress Network::UdpPacket::getAddress() const {
  return _hostAddress;
}

uint16      Network::UdpPacket::getPort() const {
  return _port;
}

void Network::UdpPacket::setFrom(const HostAddress& hostAddress, uint16 port) {
	_hostAddress = hostAddress;
	_port = port;
}