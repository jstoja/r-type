/*
** Player.h for r-type in /home/michar_l//r-type/Server/src
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 09:34:24 2012 loick michard
*/

#ifndef _PLAYER_H_
# define _PLAYER_H_

# include <map>
# include "Network/ASocket.h"
# include "Network/Proxy.hpp"
# include "Network/TcpPacket.h"

class Player : public Network::IProxyDelegate<Network::TcpPacket> {
 public:
  Player(Network::ASocket*);
  ~Player();

  void	newPacket(Network::TcpPacket*);
  void	packetWrited(Network::TcpPacket*);

  // Protocol functions
  void	connection(Network::TcpPacket*);

  typedef void (Player::* commandPointer)(Network::TcpPacket*);

 private:
  Network::ASocket*			_socket;
  Network::Proxy<Network::TcpPacket>	_proxy;
  std::map<int, commandPointer>		_commands;
};

#endif