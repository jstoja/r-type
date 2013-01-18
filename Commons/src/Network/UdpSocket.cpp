//
// UdpSocket.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Thu Dec 20 18:21:14 2012 loick michard
//

#include "UdpSocket.h"
#include "NetworkManager.h"
#include "OS.h"
#ifdef OS_WINDOWS
typedef int socklen_t;
#else
# define closesocket(x) close(x)
#endif

Network::UdpSocket::UdpSocket() : _readBuffer(NULL), _readMutex(),
				  _writeBuffer(NULL), _writeAddress(HostAddress::AnyAddress) {
  _fd = socket(AF_INET, SOCK_DGRAM, 0);
}

Network::UdpSocket::UdpSocket(int fd) : _fd(fd), _readBuffer(NULL), _readMutex(),
					_writeBuffer(NULL), _writeAddress(HostAddress::AnyAddress) {

}

Network::UdpSocket::~UdpSocket() {
  if (_fd != -1)
    ::closesocket(_fd);
}

int Network::UdpSocket::getId() const {
  return _fd;
}

bool Network::UdpSocket::bind(const HostAddress& address, uint16 port) {
  struct sockaddr_in addr;
  
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = address.toIPv4Address();
  addr.sin_port = htons(port);
  if (::bind(_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    return (false);
  return (true);
}

void Network::UdpSocket::read(ByteArray& biteArray, bool all, uint32) {
  Threading::MutexLocker(&(this->_readMutex));

  _reading = true;
  _readBuffer = &biteArray;
  (void)all;
}

void Network::UdpSocket::write(ByteArray const& biteArray, const HostAddress& hostAddress, uint16 port) {
  Threading::MutexLocker(&(this->_writeMutex));  

  _writing = true;
  _writeBuffer = &biteArray;
  _writePosition = 0;
  _writeAddress = hostAddress;
  _writePort = port;
}

void Network::UdpSocket::close() {
  if (_fd != -1)
    ::closesocket(_fd);
  _fd = -1;
  NetworkManager::getInstance().unregisterSocket(this);
  if (_delegate)
    _delegate->disconnection(this);
}

void  Network::UdpSocket::canRead() {
  struct sockaddr_in	addr;
  socklen_t		size = sizeof(addr);
  
  memset(&addr, 0, sizeof(addr));
  _readMutex.lock();
  _reading = false;
  int ret = recvfrom(_fd, (char*)(*_readBuffer), _readBuffer->getSize(), 0, (struct sockaddr*)&addr, &size);
  _readMutex.unlock();
  if (ret == 0)
    this->close();
  else if (ret != -1 && _delegate) {
    _readBuffer->resize(ret);
    _delegate->readFinished(this, *_readBuffer, HostAddress(inet_ntoa(addr.sin_addr)), ntohs(addr.sin_port));
  }
}

void  Network::UdpSocket::canWrite() {
  _writeMutex.lock();
  if (_writing && _writeBuffer) {
    uint32 size = (_writeBuffer->getSize() - _writePosition < writeSize) ? _writeBuffer->getSize() - _writePosition : writeSize;

    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = _writeAddress.toIPv4Address();
    addr.sin_port = htons(_writePort);
    int ret = ::sendto(_fd, &(((char const*)(*_writeBuffer))[_writePosition]), size, 0, (struct sockaddr*)&addr, sizeof(addr));
    if (ret == -1)
      size = 0;
    else
      size = ret;
    _writePosition += size;
    if (_delegate)
      _delegate->dataSent(this, *_writeBuffer, _writePosition);
    if (_writePosition == _writeBuffer->getSize()) {
      _writeMutex.unlock();
      if (_delegate)
        _delegate->writeFinished(this, *_writeBuffer);
      _writeMutex.lock();
      _writing = false;
      _writeBuffer = NULL;
      _writePosition = 0;
    }
  }
  _writeMutex.unlock();
}

uint16 Network::UdpSocket::getLocalPort() const {
  if (_fd == -1)
    return 0;
  struct sockaddr_in    addr;
  socklen_t             size = sizeof(addr);

  getsockname(_fd, (struct sockaddr*)&addr, &size);
  return ntohs(addr.sin_port);
}
