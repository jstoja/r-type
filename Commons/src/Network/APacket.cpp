//
// APacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 09:04:53 2012 loick michard
//

#include "APacket.h"

Network::APacket::APacket() : _data(0) {

}

Network::APacket::~APacket() {

}

ByteArray& Network::APacket::getData() {
  return _data;
}
