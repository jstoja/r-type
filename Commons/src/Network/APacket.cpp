//
// APacket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:04:53 2012 loick michard
//

#include "APacket.h"
#include "Debug.h"

Network::APacket::APacket() : _data(), _size(0), _curser(0) {

}

Network::APacket::~APacket() {

}

ByteArray& Network::APacket::getData() {
	return _data;
}

ByteArray const& Network::APacket::getData() const {
	return _data;
}

uint32 Network::APacket::getSize() const {
	return _size;
}/*

Network::APacket& Network::APacket::operator<<(uint32 integer) {
	write(&integer, sizeof(integer));
	return *this;
}

Network::APacket& Network::APacket::operator<<(uint64 integer) {
	write(&integer, sizeof(integer));
	return *this;
}

Network::APacket& Network::APacket::operator<<(int32 integer) {
	write(&integer, sizeof(integer));
	return *this;
}

Network::APacket& Network::APacket::operator<<(float32 val) {
	write(&val, sizeof(val));
	return *this;
}

Network::APacket& Network::APacket::operator<<(char character) {
	write(&character, sizeof(character));
	return *this;
}*/

Network::APacket& Network::APacket::operator<<(const std::string& str) {
	*this << (uint32)str.size();
	write(str.c_str(), str.size());
    this->updateData();
	return *this;
}

Network::APacket& Network::APacket::operator<<(Vec2 const& pos) {
    *this << pos.x << pos.y;
    this->updateData();
	return *this;
}

Network::APacket& Network::APacket::operator<<(Vec3 const& pos) {
    *this << pos.x << pos.y << pos.z;
    this->updateData();
	return *this;
}

Network::APacket& Network::APacket::operator<<(Rect2 const& pos) {
    *this << pos.pos << pos.size;
    this->updateData();
	return *this;
}

Network::APacket& Network::APacket::operator<<(Resource const& resource) {
	*this << resource.getId() << resource.getData();
    this->updateData();
	return *this;
}

Network::APacket& Network::APacket::operator<<(ByteArray const& data) {
	*this << data.getSize();
	write(data.getData(), data.getSize());
    this->updateData();
	return *this;
}

//Network::APacket& Network::APacket::operator>>(uint32& val) {
//	read(&val, sizeof(val));
//	return *this;
//}
//
//Network::APacket& Network::APacket::operator>>(uint64& val) {
//	read(&val, sizeof(val));
//	return *this;
//}
//
//Network::APacket& Network::APacket::operator>>(int32& val) {
//	read(&val, sizeof(val));
//	return *this;
//}
//
//Network::APacket& Network::APacket::operator>>(float32& val) {
//	read(&val, sizeof(val));
//	return *this;
//}
//
//Network::APacket& Network::APacket::operator>>(char& val) {
//	read(&val, sizeof(val));
//	return *this;
//}

Network::APacket& Network::APacket::operator>>(std::string& str) {
  uint32 size;

  *this >> size;
  std::string newStr(&_data[_curser], size);
  _curser += size;
  str = newStr;
  return *this;
}


Network::APacket& Network::APacket::operator>>(Vec2& pos) {
  return *this >> pos.x >> pos.y;
}

Network::APacket& Network::APacket::operator>>(Vec3& pos) {
  return *this >> pos.x >> pos.y >> pos.z;
}

Network::APacket& Network::APacket::operator>>(Rect2& pos) {
	return *this >> pos.pos >> pos.size;
}

Network::APacket& Network::APacket::operator>>(Resource& resource) {
	uint32	id;
	ByteArray	data;
	*this >> id >> data;
	resource.setData(data);
	resource.setId(id);
	return *this;
}

Network::APacket& Network::APacket::operator>>(ByteArray& data) {
	uint32	size;
	char	*tmp;

	*this >> size;
	tmp = new char[size];
	read(tmp, size);
	data.bufcopy(tmp, size);
	return *this;
}

void	Network::APacket::write(void const* data, uint32 size) {
	_size += size;
	_data.resize(_data.getSize() + size);
	for (uint32 i = 0; i < size; ++i)
		((char*)_data)[_data.getSize() - size + i] = ((char const*)data)[i];
}

void	Network::APacket::read(void* data, uint32 size) {
	for (uint32 i = 0; i < size; ++i)
		((char*)data)[i] = ((char*)_data)[_curser + i];
	_curser += size;
}

void    Network::APacket::updateData() {
    
}
