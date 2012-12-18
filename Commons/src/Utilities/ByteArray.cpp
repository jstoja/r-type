#include <cstring>
#include "ByteArray.h"

Utilities::ByteArray::ByteArray() {
  _buffer = NULL;
  _size = 0;
}

Utilities::ByteArray::ByteArray(char *buffer,  uint32 size) {
  _buffer = buffer;
  _size = size;
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

char*		Utilities::ByteArray::getBuffer() const {
  return _buffer;
}

uint32		Utilities::ByteArray::getSize() const {
  return _size;
}

void		Utilities::ByteArray::setSize(uint32 size) {
  _size = size;
}

void		Utilities::ByteArray::setBuffer(char *buffer) {
  _buffer = buffer;
}

void		Utilities::ByteArray::setAll(char *buffer, uint32 size) {
  _buffer = buffer;
  _size = size;
}
