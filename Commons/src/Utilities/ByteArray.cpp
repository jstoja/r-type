#include <cstring>
#include "ByteArray.h"

Utilities::ByteArray::ByteArray() {
  _buffer = NULL;
  _size = 0;
}

Utilities::ByteArray::ByteArray(const char *buffer,  uint32 size) {
  setAll(buffer, size);
}

Utilities::ByteArray::ByteArray(ByteArray const& cpy) {
  setAll(cpy.getBuffer(), cpy.getSize());
}

Utilities::ByteArray::~ByteArray() {
}

Utilities::ByteArray&	Utilities::ByteArray::operator=(ByteArray const& cpy) {
  setAll(cpy.getBuffer(), cpy.getSize());
  return *this;
}

bool		Utilities::ByteArray::operator==(ByteArray const& cmp) {
  if (std::strncmp(_buffer,  cmp.getBuffer(), _size) == 0)
    return true;
  return false;
}

bool		Utilities::ByteArray::operator!=(ByteArray const& cmp) {
  if (std::strncmp(_buffer,  cmp.getBuffer(), _size) == 0) 
    return false;
  return true;
}

Utilities::ByteArray&	Utilities::ByteArray::operator<<(ByteArray const& cpy)
{
  append(cpy);
  return *this;
}

char*	Utilities::ByteArray::getBuffer() const {
  return _buffer;
}

uint32	Utilities::ByteArray::getSize() const {
  return _size;
}

void	   Utilities::ByteArray::setSize(uint32 size) {
  _size = size;
}

void	  Utilities::ByteArray::setAll(const char *buffer, uint32 size) {
  _buffer = new char[size];
  std::strncpy(_buffer, buffer, size);
  _size = size;
}

void	  Utilities::ByteArray::append(ByteArray const& cpy) {
  append(cpy.getBuffer(), cpy.getSize());
}

void    Utilities::ByteArray::append(char *buffer, uint32 size) {
  char	*tmp;

  tmp = new char[_size];
  std::strncpy(tmp, _buffer, _size);
  _buffer = new char[_size + size];
  std::strncpy(_buffer, tmp, _size);
  std::strncat(_buffer, buffer, size);
  _size += size;
  delete [] tmp;
}

std::ostream&	operator<<(std::ostream &os, Utilities::ByteArray const& b) {
  return os << b.getBuffer();
}
