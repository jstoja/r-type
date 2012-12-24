//
// main.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 21:45:54 2012 loick michard
//

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif
#include <iostream>
#include <cstdio>
#include "Network/TcpServer.h"
#include "Network/ISocketDelegate.h"
#include "Network/ITcpServerDelegate.h"
#include "Network/ASocket.h"

using namespace Network;

class Test : public Network::ISocketDelegate, public Network::ITcpServerDelegate {
public:
  Test() : _array(5), _other(1000) {
    for (unsigned int i = 0; i < 1000; ++i) {
      ((char*)_other)[i] = 's';
    }
  }

  void newConnection(Network::ASocket* socket) {
    socket->setDelegate(this);
    std::cout << "New connection" << std::endl;
    socket->read(_array, false);
  }

  void readFinished(Network::ASocket* socket, ByteArray& array,
		    const Network::HostAddress& hostAddress, uint16 port) {
    std::cout << "RECEIVE [";
    std::cout.write((char*)array, array.getSize());
    std::cout << "] from " << hostAddress.getString() << ":" << port << std::endl;
    //_other = array;
    socket->write(_other);
    socket->read(_array);
  }

  void dataReceived(Network::ASocket* socket, ByteArray& array, uint32 size) {
    std::cout << "Receive " << size << " of " << array.getSize() << std::endl;
    (void)socket;
  }

  void writeFinished(Network::ASocket* socket, ByteArray& array) {
    std::cout << "Write finished -> " << array.getSize() << std::endl;
    (void)socket;
  }

  void dataSent(Network::ASocket* socket, ByteArray& array, uint32 size) {
    std::cout << "Send " << size << " of " << array.getSize() << std::endl;
    (void)socket;
  }

  void disconnection(Network::ASocket* socket) {
    delete socket;
  }

private:
  ByteArray _array;
  ByteArray _other;
};

int main() {
  Network::TcpServer server;
  Test		     test;

  server.setDelegate(&test);
  if (server.listen())
    std::cout << "Server started on port : " << server.getLocalPort() << std::endl;

  getchar();
}
