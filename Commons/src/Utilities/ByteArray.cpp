#include <cstring>
#include <algorithm>
#include "ByteArray.h"

Utilities::ByteArray::ByteArray() {  
}

Utilities::ByteArray::ByteArray(const char *buffer,  uint32 size) {
  bufcopy(buffer, size);
}

Utilities::ByteArray::ByteArray(ByteArray const& cpy) {
  bufcopy(cpy.getBuffer());
}

Utilities::ByteArray::~ByteArray() {
}

Utilities::ByteArray&	Utilities::ByteArray::operator=(ByteArray const& cpy) {
  bufcopy(cpy.getBuffer());
  return *this;
}

bool		Utilities::ByteArray::operator==(ByteArray const& cmp) {
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

bool		Utilities::ByteArray::operator!=(ByteArray const& cmp) {
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

Utilities::ByteArray&	Utilities::ByteArray::operator<<(ByteArray const& cpy)
{
  append(cpy);
  return *this;
}

std::vector<char>	Utilities::ByteArray::getBuffer() const {
  return _buffer;
}

uint32	Utilities::ByteArray::getSize() const {
  return _buffer.size();
}

void	  Utilities::ByteArray::append(ByteArray const& cpy) {
  uint64 bufsize = cpy.getSize();
  uint64 pos = getSize();
  std::vector<char> buf = cpy.getBuffer();
  
  _buffer.resize(getSize() + bufsize);
  for (uint32 i = 0; i < bufsize; ++i)
    _buffer[pos++] = buf[i];
}

void    Utilities::ByteArray::append(char *buffer, uint32 size) {
  uint32 pos = getSize();

  _buffer.resize(getSize() + size);
  for (uint32 i = 0; i < size; ++i)
    _buffer[pos++] = buffer[i];
}

void	Utilities::ByteArray::bufcopy(const char* buffer, uint32 size) {
  _buffer.resize(size);
  for (uint32 i = 0; i < size; ++i)
    _buffer[i] = buffer[i];
}

void	Utilities::ByteArray::bufcopy(std::vector<char> const& buffer) {
 _buffer.resize(buffer.size());
 copy(buffer.begin(), buffer.end(), _buffer.begin());
 }

void	Utilities::ByteArray::debug() const {
  std::cout << "### DEBUG BYTE ARRAY ###" << std::endl;
  std::cout << "SIZE " << _buffer.size() << std::endl;
  for (uint32 i = 0; i < _buffer.size(); ++i)
    std::cout << "[" << _buffer[i] << "]";
  std::cout << std::endl;
  std::cout << "###################" << std::endl;
}
