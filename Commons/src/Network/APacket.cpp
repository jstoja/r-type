//
// APacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 09:04:53 2012 loick michard
//

#include "APacket.h"

Network::APacket::APacket() : _data(0), _size(0), _curser(0) {

}

Network::APacket::~APacket() {

}

ByteArray& Network::APacket::getData() {
  return _data;
}

uint32 Network::APacket::getSize() const {
  return _size;
}

Network::APacket& Network::APacket::operator<<(uint32 integer) {
  _size += sizeof(uint32);
  _data.resize(_data.getSize() + sizeof(uint32));
  *((int*)(&((char*)_data)[_data.getSize() - sizeof(uint32)])) = integer;
  return *this;
}

Network::APacket& Network::APacket::operator<<(float32 val) {
  _size += sizeof(float32);
  _data.resize(_data.getSize() + sizeof(float32));
  *((float32*)(&((char*)_data)[_data.getSize() - sizeof(float32)])) = val;
  return *this;
}

Network::APacket& Network::APacket::operator<<(char character) {
  _size += 1;
  _data.resize(_data.getSize() + 1);
  *((char*)(&((char*)_data)[_data.getSize() - 1])) = character;
  return *this;
}

Network::APacket& Network::APacket::operator<<(const std::string& str) {
  *this << (uint32)str.size();
  _size += str.size();
  _data.resize(_data.getSize() + str.size());
  for (unsigned int i = 0; i < str.size(); ++i)
    _data[_data.getSize() - str.size() + i] = str[i];
  return *this;
}

Network::APacket& Network::APacket::operator<<(Vec2 const& pos) {
  _size += 8;
  _data.resize(_data.getSize() + 8);
  *((int*)(&((char*)_data)[_data.getSize() - 8])) = pos.x;
  *((int*)(&((char*)_data)[_data.getSize() - 4])) = pos.y;
  return *this;
}

Network::APacket& Network::APacket::operator<<(Vec3 const& pos) {
  _size += 12;
  _data.resize(_data.getSize() + 12);
  *((int*)(&((char*)_data)[_data.getSize() - 12])) = pos.x;
  *((int*)(&((char*)_data)[_data.getSize() - 8])) = pos.y;
  *((int*)(&((char*)_data)[_data.getSize() - 4])) = pos.z;
  return *this;
}

Network::APacket& Network::APacket::operator<<(Rect2 const& pos) {
	return *this << pos.pos << pos.size;
}

Network::APacket& Network::APacket::operator>>(uint32& integer) {
  integer = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  return *this;
}

Network::APacket& Network::APacket::operator>>(float32& val) {
  val = *((float32*)(&((char*)_data)[_curser]));
  _curser += sizeof(float32);
  return *this;
}

Network::APacket& Network::APacket::operator>>(char& character) {
  character = *((char*)(&((char*)_data)[_curser]));
  _curser += 1;
  return *this;
}

Network::APacket& Network::APacket::operator>>(std::string& str) {
  uint32 size;

  *this >> size;
  std::cout << size << std::endl; 
  std::string newStr(&_data[_curser], size);
  _curser += str.size();
  str = newStr;
  return *this;
}


Network::APacket& Network::APacket::operator>>(Vec2& pos) {
  pos.x = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  pos.y = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  return *this;
}

Network::APacket& Network::APacket::operator>>(Vec3& pos) {
  pos.x = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  pos.y = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  pos.y = *((uint32*)(&((char*)_data)[_curser]));
  _curser += sizeof(uint32);
  return *this;
}

Network::APacket& Network::APacket::operator>>(Rect2& pos) {
	return *this >> pos.pos >> pos.size;
}