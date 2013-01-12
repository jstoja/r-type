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
# include "Player.h"

class Server : public Network::ITcpServerDelegate {
public:
  Server();
  ~Server();

  void newConnection(Network::ASocket*);
  static std::string const&	getPluginDirectory();
  static void				setPluginDirectory(std::string const& dir);

private:
	static std::string	_pluginDirectory;
	Network::TcpServer	_tcpServer;
	std::vector<Player*>	_players;
};

#endif
