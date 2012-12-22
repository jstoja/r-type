#include <cstring>
#include <algorithm>
#include "ByteArray.h"

ByteArray::ByteArray() {  
}

ByteArray::ByteArray(const char *buffer,  uint32 size) {
  bufcopy(buffer, size);
}

ByteArray::ByteArray(uint32 size) {
  _buffer.resize(size);
}

ByteArray::ByteArray(ByteArray const& cpy) {
  bufcopy(cpy.getBuffer());
}

ByteArray::~ByteArray() {
}

ByteArray&	ByteArray::operator=(ByteArray const& cpy) {
  bufcopy(cpy.getBuffer());
  return *this;
}

bool		ByteArray::operator==(ByteArray const& cmp) {
  uint64	bufsize = cmp.getSize();
  uint64	currentSize = getSize();
  if (bufsize != currentSize)
    return false;
  std::vector<char> buf = cmp.getBuffer();
  for (uint64 i = 0; i < bufsize; ++i)
    if (buf[i] != _buffer[i])
      return false;
  return true;
}

bool		ByteArray::operator!=(ByteArray const& cmp) {
  uint64	bufsize = cmp.getSize();
  uint64	currentSize = getSize();
  if (bufsize != currentSize)
    return true;
  std::vector<char> buf = cmp.getBuffer();
  for (uint32 i = 0; i < bufsize; ++i)
    if (buf[i] != _buffer[i])
      return true;
  return false;
}

ByteArray&	ByteArray::operator<<(ByteArray const& cpy) {
  append(cpy);
  return *this;
}

ByteArray::operator char*() {
  return (char*)&_buffer[0];
}

std::vector<char>	ByteArray::getBuffer() const {
  return _buffer;
}

uint32	ByteArray::getSize() const {
  return _buffer.size();
}

void ByteArray::resize(uint32 size) {
  _buffer.resize(size);
}

void	  ByteArray::append(ByteArray const& cpy) {
  uint64 bufsize = cpy.getSize();
  uint64 pos = getSize();
  std::vector<char> buf = cpy.getBuffer();
  
  _buffer.resize(getSize() + bufsize);
  for (uint32 i = 0; i < bufsize; ++i)
    _buffer[pos++] = buf[i];
}

void    ByteArray::append(char *buffer, uint32 size) {
  uint32 pos = getSize();

  _buffer.resize(getSize() + size);
  for (uint32 i = 0; i < size; ++i)
    _buffer[pos++] = buffer[i];
}

void	ByteArray::bufcopy(const char* buffer, uint32 size) {
  _buffer.resize(size);
  for (uint32 i = 0; i < size; ++i)
    _buffer[i] = buffer[i];
}

void	ByteArray::bufcopy(std::vector<char> const& buffer) {
 _buffer.resize(buffer.size());
 copy(buffer.begin(), buffer.end(), _buffer.begin());
 }

void	ByteArray::debug() const {
  std::cout << "### DEBUG BYTE ARRAY ###" << std::endl;
  std::cout << "SIZE " << _buffer.size() << std::endl;
  for (uint32 i = 0; i < _buffer.size(); ++i)
    std::cout << "[" << _buffer[i] << "]";
  std::cout << std::endl;
  std::cout << "###################" << std::endl;
}
