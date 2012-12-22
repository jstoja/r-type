//
// TcpSocket.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 22:30:18 2012 loick michard
//

#include <iostream>
#include <cstring>
#include "OS.h"
#ifdef OS_WINDOWS
# include <winsock2.h>
typedef int socklen_t;
#else
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# define closesocket(x) close(x)
#endif
#include "TcpSocket.h"

Network::TcpSocket::TcpSocket() : _hostAddress(HostAddress::AnyAddress), _hostPort(0),
				  _toRead(0), _bufferToRead(NULL), 
				  _bufferToWrite(NULL), _writePosition(0) {
  _fd = socket(AF_INET, SOCK_STREAM, 0); //  | SOCK_NONBLOCK
  if (_fd == -1)
    std::cout << "Failed to create TcpSocket" << std::endl;
}

Network::TcpSocket::TcpSocket(int fd) : _hostAddress(HostAddress::AnyAddress), _hostPort(0),
					_toRead(0), _bufferToRead(NULL), 
					_bufferToWrite(NULL), _writePosition(0) {
  _fd = fd;
  _reading = true;
  _listening = false;
}

Network::TcpSocket::~TcpSocket() {
  if (_fd != -1)
    ::closesocket(_fd);
}

int Network::TcpSocket::getId() const {
  return _fd;
}

bool Network::TcpSocket::connect(const HostAddress& address, uint16 port) {
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = address.toIPv4Address();
  addr.sin_port = htons(port);
  if (::connect(_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (false);

  _reading = true;
  _listening = false;
  _hostAddress = address;
  _hostPort = port;
  return (true);
}

bool Network::TcpSocket::listen(const HostAddress& address, uint16 port) {
  struct sockaddr_in addr;

  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET ;
  addr.sin_addr.s_addr = address.toIPv4Address();
  addr.sin_port = htons(port);
  if (::bind(_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (false);
  if (::listen(_fd, 100) == -1)
    return (false);
  _reading = false;
  _listening = true;
  return (true);
}

void Network::TcpSocket::write(ByteArray& biteArray, const HostAddress& hostAddress, uint16 port) {
  (void)hostAddress;
  (void)port;

  Threading::MutexLocker locker(&_bufferToWriteMutex);
  _writing = true;
  _writePosition = 0;
  _bufferToWrite = &biteArray;
}

void Network::TcpSocket::read(ByteArray& biteArray, bool all) {
  uint32 size = biteArray.getSize();
  
  _bufferToReadMutex.lock();
  _bufferMutex.lock();
  if (_buffer.getSize() >= size) {
    for (unsigned int i = 0; i < size; ++i)
      ((char*)biteArray)[i] = ((char*)_buffer)[i];
    for (unsigned int i = size; i < _buffer.getSize(); ++i)
      ((char*)_buffer)[i - size] = ((char*)_buffer)[i];
    _buffer.resize(_buffer.getSize() - size);
  } else if (_buffer.getSize() && !_readAll) {
    size = (_buffer.getSize() > size) ? size : _buffer.getSize();
    biteArray.resize(size);
    for (unsigned int i = 0; i < size; ++i)
      ((char*)biteArray)[i] = ((char*)_buffer)[i];
    for (unsigned int i = size; i < _buffer.getSize(); ++i)
      ((char*)_buffer)[i - size] = ((char*)_buffer)[i];
    _buffer.resize(_buffer.getSize() - size);
  } else {
    _toRead = size;
    _bufferToRead = &biteArray;
    _readAll = all;
    _bufferToReadMutex.unlock();
    _bufferMutex.unlock();
    if (_delegate)
      _delegate->dataReceived(this, biteArray, _buffer.getSize());
    return;
  }
  _toRead = 0;
  _bufferToRead = NULL;
  _bufferToReadMutex.unlock();
  _bufferMutex.unlock();
  if (_delegate)
    _delegate->readFinished(this, biteArray, _hostAddress, _hostPort);
}

void Network::TcpSocket::close() {
  ::closesocket(_fd);
  _fd = -1;
  NetworkManager::getInstance().unregisterSocket(this);
  if (_delegate)
    _delegate->disconnection(this);
}

void Network::TcpSocket::canRead() {
  if (_listening) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    memset(&addr, 0, sizeof(addr));
    int ret = ::accept(_fd, (struct sockaddr*)&addr, &len);
    if (ret != -1 && _delegate) {
      TcpSocket* newConnection = new TcpSocket(ret);
      newConnection->_hostAddress = HostAddress(inet_ntoa(addr.sin_addr));
      newConnection->_hostPort = ntohs(addr.sin_port);
      _delegate->newConnection(newConnection);
    }
  }
  else if (_reading) {
    { 
      Threading::MutexLocker locker(&_bufferMutex);
      unsigned int size = _buffer.getSize();
      _buffer.resize(size + (_toRead) ? _toRead : readSize);
      int ret = ::recv(_fd, &(((char*)_buffer)[size]), (_toRead) ? _toRead : readSize, 0);
      if (ret == 0) {
	this->close();
	return;
      }
      if (ret == -1)
	_buffer.resize(size);
      else
	_buffer.resize(size + ret);
    }
    if (_bufferToRead)
      this->read(*_bufferToRead);
  }
}

void Network::TcpSocket::canWrite() {
  _bufferToWriteMutex.lock();
  if (_writing && _bufferToWrite) {
    uint32 size = (_bufferToWrite->getSize() - _writePosition < writeSize) ? _bufferToWrite->getSize() - _writePosition : writeSize;

    int ret = ::send(_fd, &(((char*)(*_bufferToWrite))[_writePosition]), size, 0);
    if (ret == -1)
      size = 0;
    else
      size = ret;
    _writePosition += size;
    if (_delegate)
      _delegate->dataSent(this, *_bufferToWrite, _writePosition);
    if (_writePosition == _bufferToWrite->getSize()) {
      _bufferToWriteMutex.unlock();
      if (_delegate)
	_delegate->writeFinished(this, *_bufferToWrite);
      _bufferToWriteMutex.lock();
      _writing = false;
      _bufferToWrite = NULL;
      _writePosition = 0;
    }
  }
  _bufferToWriteMutex.unlock();
}

uint16 Network::TcpSocket::getLocalPort() const {
  if (_fd == -1)
    return 0;
  struct sockaddr_in    addr;
  socklen_t             size = sizeof(addr);

  getsockname(_fd, (struct sockaddr*)&addr, &size);
  return ntohs(addr.sin_port);
}
