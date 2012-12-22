//
// main.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 21:45:54 2012 loick michard
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Network/TcpServer.h"
#include "Network/ISocketDelegate.h"
#include "Network/ITcpServerDelegate.h"
#include "Network/ASocket.h"
#include "Network/UdpSocket.h"

using namespace Network;

int id = 0;

class Test : public Network::ISocketDelegate, public Network::ITcpServerDelegate {
public:
  Test() : _array(5), _other("trop bien", 9) {
  }

  void newConnection(Network::ASocket* socket) {
  }

  void readFinished(Network::ASocket* socket, ByteArray& array,
		    const Network::HostAddress& hostAddress, uint16 port) {
    std::cout << "RECEIVE [";
    std::cout.write((char*)array, array.getSize());
    std::cout << "] from " << hostAddress.getString() << ":" << port << std::endl;
    //_other = array;
    if (id == 1)
      socket->write(_other, hostAddress, port);
    //socket->read(_array);
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

int main(int ac, char** av) {
  Network::UdpSocket socket;
  Test		     test;
  ByteArray array(100);
  ByteArray warray("salut ca va?", 12);

  id = atoi(av[1]);
  if (av[1][0] == '1') {
    socket.setDelegate(&test);
    if (socket.bind())
      std::cout << "Socket bind on port : " << socket.getLocalPort() << std::endl;
    socket.read(array);
  }
  else if (av[1][0] == '2') {
    socket.write(warray, Network::HostAddress(av[2]), atoi(av[3]));
    socket.read(array);
  }
  
  getchar();
}
