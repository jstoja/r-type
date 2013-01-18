//
// Player.cpp for r-type in /home/michar_l//r-type/Server/src
//
// Made by loick michard
// Login   <michar_l@epitech.net>
//
// Started on  Sun Dec 23 09:35:41 2012 loick michard
//

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Debug.h"

Player::Player(Network::ASocket* socket, IServerDelegate* server) : _isReady(false), _socket(socket), _proxy(socket, this), _server(server) {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex.push_back(new Threading::Mutex());
    }
    
    Log("New Player");

    _commands[Network::Proxy<Network::TcpPacket>::AuthenficitationConnection] = &Player::connection;
    _commands[Network::Proxy<Network::TcpPacket>::InformationsGameList] = &Player::listGame;
    _commands[Network::Proxy<Network::TcpPacket>::GameJoin] = &Player::joinGame;
    _commands[Network::Proxy<Network::TcpPacket>::GameCreate] = &Player::createGame;
    _commands[Network::Proxy<Network::TcpPacket>::GameReady] = &Player::readyToStart;
}

Player::~Player() {
    delete _socket;
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

void Player::packetReceived(Network::TcpPacket* packet) {
    uint32 code, size;

    *packet >> code >> size;
    std::cout << code << " -> Size : " << size << std::endl;
    _attributesMutex[eCommands]->lock();
    std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
    if (it != _commands.end())
        (this->*(it->second))(packet);
    _attributesMutex[eCommands]->unlock();
    delete packet;
}

void Player::packetSent(Network::TcpPacket const* packet) {
    delete packet;
}

void Player::connectionClosed(Network::Proxy<Network::TcpPacket>*) {
    _server->quitGame(this);
}

void Player::connection(Network::TcpPacket* packet) {
    std::string login;

    *packet >> login;
    std::cout << "Connection with login " << login << std::endl;

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(0x01000000);
    *tcpPacket << (uint32)42;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
    delete packet;
}

void  Player::sendPacket(Network::Proxy<Network::TcpPacket>::ToSend const& toSend) {
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
}

void Player::createGame(Network::TcpPacket* packet) {
    Game *game = new Game(packet);

    _attributesMutex[eServer]->lock();
    bool gameCreated = _server->createGame(game, this);
    _attributesMutex[eServer]->unlock();

    if (gameCreated == false) {
        delete game;
    }

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(0x01020300 + (gameCreated ? 3 : 1));
    *tcpPacket << *game;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
    delete packet;
}

void Player::joinGame(Network::TcpPacket* packet) {
    uint32 id;

    *packet >> id;
    _attributesMutex[eProxy]->lock();
    int code = 0x01020000 + _server->joinGame(id, this);

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(code);
    *tcpPacket << id;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();

    _server->sendResources(id, this);
    _attributesMutex[eServer]->unlock();
    delete packet;
}

void Player::listGame(Network::TcpPacket* packet) {
    _attributesMutex[eServer]->lock();
    std::map<uint32, Game*> games = _server->getGames();
    _attributesMutex[eServer]->unlock();

    std::list<Game*> newGamesList;
    for (int i = 0; i < games.size(); ++i) {
        newGamesList.push_back(games[i]);
    }

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(0x01010100);
    *tcpPacket << newGamesList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
    delete packet;
}

void Player::readyToStart(Network::TcpPacket* packet) {
    uint32 gameId;

    *packet >> gameId;
    _attributesMutex[eIsReady]->lock();
    _isReady = true;
    _attributesMutex[eIsReady]->unlock();

    _attributesMutex[eServer]->lock();
    _server->playerReady(gameId, this);
    _attributesMutex[eServer]->unlock();
}


Network::APacket&       operator<<(Network::APacket& packet, Player const& player) {
    packet << player.getId();
    return packet;
}