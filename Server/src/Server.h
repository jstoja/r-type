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
# include "IServerDelegate.h"

class Server : public Network::ITcpServerDelegate, public IServerDelegate {
public:
  Server();
  ~Server();

    int             run();
    void            newConnection(Network::ASocket*);

    virtual std::string                     getName(void) const;
    virtual std::map<uint32, Game*> const&  getGames(void) const;
    virtual bool                            canAddPlayer(std::string const& name);

    virtual bool    createGame(Game* game, Player* player);
    virtual int     joinGame(uint32 gameId, Player* player);
    virtual void    quitGame(Player* player);
    virtual void    sendResources(uint32 gameId, Player* player);
    virtual void    playerReady(uint32 gameId, Player* player);
    virtual void    gameStart(uint32 gameId);
    virtual void    listPlayers(uint32 gameId, Player* player);
    virtual void    sendGameInfo(uint32, Player*);

    static std::string const& getPluginDirectory();
    static void               setPluginDirectory(std::string const& dir);

private:
    static std::string      _pluginDirectory;
    Network::TcpServer      _tcpServer;
    std::vector<Player*>    _players;
    std::map<uint32, Game*> _games;

	static const uint32		_sendFramerate = 40;
};

#endif
