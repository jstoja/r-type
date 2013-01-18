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
#include "Debug.h"
#include "Threading/Thread.h"

Network::TcpSocket::TcpSocket(ISocketDelegate* delegate) :
_hostAddress(HostAddress::AnyAddress), _hostPort(0), _toRead(0),
_bufferToRead(NULL), _bufferToWrite(NULL), _writePosition(0), _connectionAddress("") {
    setDelegate(delegate);
  _fd = socket(AF_INET, SOCK_STREAM, 0); //  | SOCK_NONBLOCK
  if (_fd == -1)
    Log("Failed to create TcpSocket");
}

Network::TcpSocket::TcpSocket(int fd) : _hostAddress(HostAddress::AnyAddress), _hostPort(0),
					_toRead(0), _bufferToRead(NULL),
					_bufferToWrite(NULL), _writePosition(0), _connectionAddress("") {
  _fd = fd;
  _reading = true;
  _listening = false;
}

Network::TcpSocket::~TcpSocket() {
    NetworkManager::getInstance().unregisterSocket(this);    
  if (_fd != -1)
    ::closesocket(_fd);
}

int Network::TcpSocket::getId() const {
  return _fd;
}

void Network::TcpSocket::operator()() {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = _connectionAddress.toIPv4Address();
    addr.sin_port = htons(_connectionPort);
    if (::connect(_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        _delegate->connectionFinished(this, false);
        return;
    }

    _reading = true;
    _listening = false;
    _hostAddress = _connectionAddress;
    _hostPort = _connectionPort;
    _delegate->connectionFinished(this, true);
}

void Network::TcpSocket::connect(const HostAddress& address, uint16 port) {
  _connectionAddress = address;
  _connectionPort = port;
  Threading::Thread<Network::TcpSocket> thread(this);
  thread.run();
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

void Network::TcpSocket::write(ByteArray const& byteArray, const HostAddress& hostAddress, uint16 port) {
  (void)hostAddress;
  (void)port;

  Threading::MutexLocker locker(&_bufferToWriteMutex);
  _writing = true;
  _writePosition = 0;
  _bufferToWrite = &byteArray;
}

void Network::TcpSocket::read(ByteArray& biteArray, bool all, uint32 start) {
  uint32 size = biteArray.getSize() - start;

  _bufferToReadMutex.lock();
  _bufferMutex.lock();
  if (_buffer.getSize() >= size) {
    for (unsigned int i = 0; i < size; ++i)
      ((char*)biteArray)[i + start] = ((char*)_buffer)[i];
    for (unsigned int i = size; i < _buffer.getSize(); ++i)
      ((char*)_buffer)[i - size] = ((char*)_buffer)[i];
    _buffer.resize(_buffer.getSize() - size);
  } else if (_buffer.getSize() && !_readAll) {
    size = (_buffer.getSize() > size) ? size : _buffer.getSize();
    biteArray.resize(size);
    for (unsigned int i = 0; i < size; ++i)
      ((char*)biteArray)[i + start] = ((char*)_buffer)[i];
    for (unsigned int i = size; i < _buffer.getSize(); ++i)
      ((char*)_buffer)[i - size] = ((char*)_buffer)[i];
    _buffer.resize(_buffer.getSize() - size);
  } else {
    _toRead = size;
    _bufferToRead = &biteArray;
    _readAll = all;
    _readStart = start;
    _bufferToReadMutex.unlock();
    _bufferMutex.unlock();
    if (_delegate)
        _delegate->dataReceived(this, _buffer, biteArray.getSize());
    return;
  }
  _toRead = 0;
  _bufferToRead = NULL;
  _readStart = 0;
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
      this->read(*_bufferToRead, _readAll, _readStart);
  }
}

void Network::TcpSocket::canWrite() {
    _bufferToWriteMutex.lock();
    if (_writing && _bufferToWrite) {
        uint32 size = (_bufferToWrite->getSize() - _writePosition < writeSize) ? _bufferToWrite->getSize() - _writePosition : writeSize;

        int ret = ::send(_fd, &(((const char*)(*_bufferToWrite))[_writePosition]), size, 0);
        if (ret == -1)
            size = 0;
        else
            size = ret;
        _writePosition += size;
        if (_delegate)
            _delegate->dataSent(this, *_bufferToWrite, _writePosition);
        if (_writePosition == _bufferToWrite->getSize()) {
            _writing = false;
            _bufferToWrite = NULL;
            _writePosition = 0;
            _bufferToWriteMutex.unlock();
            if (_delegate)
                _delegate->writeFinished(this, *_bufferToWrite);
            _bufferToWriteMutex.lock();
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
