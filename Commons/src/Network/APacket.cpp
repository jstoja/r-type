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
  _size += 4;
  _data.resize(_data.getSize() + 4);
  *((int*)(&((char*)_data)[_data.getSize() - 4])) = integer;
  return *this;
}

Network::APacket& Network::APacket::operator<<(const std::string& str) {
  *this << str.size();
  _size += str.size();
  _data.resize(_data.getSize() + str.size());
  for (unsigned int i = 0; i < str.size(); ++i)
    _data[_data.getSize() - str.size() + i] = str[i];
  return *this;
}

Network::APacket& Network::APacket::operator>>(uint32& integer) {
  integer = *((int*)(&((char*)_data)[_curser]));
  _curser += 4;
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

template <typename T>
Network::APacket& Network::APacket::operator<<(const std::list<T*>& elements) {
  typename std::list<T*>::const_iterator it;

  *this << elements.size();
  for (it = elements.begin(); it != elements.end(); ++it) {
    *this << *(*it);
  }
}

template <typename T>
Network::APacket& Network::APacket::operator<<(const std::list<T>& elements) {
  typename std::list<T*>::const_iterator it;

  *this << elements.size();
  for (it = elements.begin(); it != elements.end(); ++it) {
    *this << (*it);
  }
}

template <typename T>
Network::APacket& Network::APacket::operator>>(std::list<T*>& elements) {
  uint32 size;

  *this >> size;
  for (uint32 i = 0; i < size; ++i) {
    T* element = new T;
    *this >> *element;
    elements.push_front(element);
  }
}

template <typename T>
Network::APacket& Network::APacket::operator>>(std::list<T>& elements) {
  uint32 size;

  *this >> size;
  for (uint32 i = 0; i < size; ++i) {
    T element;
    *this >> element;
    elements.push_front(element);
  }  
}
