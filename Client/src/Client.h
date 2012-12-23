/*
** Client.h for r-type in /home/michar_l//r-type
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 13:57:28 2012 loick michard
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#include "Network/TcpSocket.h"
#include "Network/Proxy.hpp"
#include "Network/IProxyDelegate.h"
#include "Network/TcpPacket.h"

class Client : public Network::IProxyDelegate<Network::TcpPacket> {
 public:
  Client(const std::string& ip, uint16 port);
  ~Client();

  void	newPacket(Network::TcpPacket* packet);
  void	packetWrited(Network::TcpPacket* packet);

  void	connection(const std::string& name);
  
 private:
  Network::TcpSocket			_tcpSocket;
  Network::Proxy<Network::TcpPacket>*	_proxy;
};

#endif
