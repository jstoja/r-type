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
# include <vector>
# include <map>
# include "Network/TcpServer.h"
# include "Game.h"
# include "Player.h"

class Server : public Network::ITcpServerDelegate, public IServerDelegate {
public:
  Server();
  ~Server();

  void newConnection(Network::ASocket*);

  virtual bool  createGame(Game* game, Player* player);
  //virtual void  listGame(Network::ASocket* socket);
  virtual int   joinGame(std::string const& gameName, Player* player);
  virtual void  quitGame(uint32 gameId, Player* player);

private:
  Network::TcpServer	_tcpServer;
  std::vector<Player*>  _players;
  std::map<std::string, IGame*>	_games;
};

#endif
