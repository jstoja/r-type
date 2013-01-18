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
# include "Network/TcpSocket.h"
# include "Network/TcpPacket.h"
# include "Game.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"
# include "IServerDelegate.h"

class Player : public Network::IProxyDelegate<Network::TcpPacket>, public Object {
public:
    Player(Network::ASocket*, IServerDelegate* server);
    virtual ~Player();

    void    packetReceived(Network::TcpPacket*);
    void    packetSent(Network::TcpPacket const*);
    void    connectionClosed(Network::Proxy<Network::TcpPacket>*);
    void    sendPacket(Network::Proxy<Network::TcpPacket>::ToSend const& toSend);

    // Protocol functions
    void  connection(Network::TcpPacket*);
    void  createGame(Network::TcpPacket*);
    void  joinGame(Network::TcpPacket*);
    void  listGame(Network::TcpPacket* packet);
    void  readyToStart(Network::TcpPacket* packet);

    bool isReady(void);

    typedef void (Player::* commandPointer)(Network::TcpPacket*);

private:

    enum    _mutexVariable {
        eIsReady = 0,
        eSocket,
        eProxy,
        eUdpProxy,
        eServer,
        eCommands,
        eLastAttribute
    };
    std::vector<Threading::Mutex*>        _attributesMutex;

    bool                                  _isReady;
    Network::ASocket*                     _socket;
    Network::Proxy<Network::TcpPacket>    _proxy;
    IServerDelegate*                      _server;
    std::map<int, commandPointer>         _commands;
};

Network::APacket&       operator<<(Network::APacket& packet, Player const& player);

#endif
