//
// Server.hpp for r-type in /home/michar_l//r-type/Server/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 09:19:04 2012 loick michard
//

#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include <iostream>
# include "Network/TcpServer.h"
# include "Client.h"

class Server : public Network::ITcpServerDelegate {
public:
  Server();
  ~Server();

  void newConnection(Network::ASocket*);
private:
  Network::TcpServer	_tcpServer;
  std::vector<Client*>	_clients;
};

#endif
