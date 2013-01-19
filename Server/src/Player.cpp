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

Player::Player(Network::ASocket* socket, IServerDelegate* server) :
_attributesMutex() ,_isReady(false), _name(), _socket(socket),
_proxy(socket, this), _server(server), _commands() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex.push_back(new Threading::Mutex());
    }

    Log("New Player");

    _commands[Network::TcpProxy::AuthenficitationConnection] = &Player::connection;
    _commands[Network::TcpProxy::InformationsGeneral] = &Player::serverInfos;
    _commands[Network::TcpProxy::InformationsGameList] = &Player::listGame;
    _commands[Network::TcpProxy::GameJoin] = &Player::joinGame;
    _commands[Network::TcpProxy::GameCreate] = &Player::createGame;
    _commands[Network::TcpProxy::PlayerReady] = &Player::readyToStart;
    _commands[Network::TcpProxy::PlayerList] = &Player::playerList;
    _commands[Network::TcpProxy::GameQuit] = &Player::quitGame;
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
    _attributesMutex[eCommands]->lock();
    std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
    if (it != _commands.end())
        (this->*(it->second))(packet);
    else {
        Log("Received unknown command 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
    }
    _attributesMutex[eCommands]->unlock();
    delete packet;
}

bool Player::isReady(void) const {
    return _isReady;
}

std::string const& Player::getName(void) const {
    return _name;
}

void Player::packetSent(Network::TcpPacket const* packet) {
    delete packet;
}

void Player::connectionClosed(Network::Proxy<Network::TcpPacket>*) {
    _server->quitServer(this);
}

void Player::connection(Network::TcpPacket* packet) {
    std::string name;
    *packet >> name;
    Log("Connection with login " << name << ", id: " << getId());
    
    uint32 code = Network::TcpProxy::AuthenficitationConnectionSuccess;
    
    if (_server->canAddPlayer(name)) {
        _name = name;
    } else {
        code = Network::TcpProxy::AuthenficitationConnectionIncorrectLogin;
    }
    
    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(code);
    *tcpPacket << (uint32)getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
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
    tcpPacket->setCode(gameCreated ? Network::TcpProxy::GameCreatedSuccess
                       : Network::TcpProxy::GameCreatedBadName);
    if (gameCreated)
        *tcpPacket << *game;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
}

void Player::joinGame(Network::TcpPacket* packet) {
    uint32 id;

    *packet >> id;
    _attributesMutex[eServer]->lock();
    int code = _server->joinGame(id, this);
    _attributesMutex[eServer]->unlock();

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(code);
    *tcpPacket << id;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();

    if (code == Network::TcpProxy::GameJoinSuccess) {
        _server->sendResources(id, this);        
        _server->sendGameInfo(id, this);
    }
    _attributesMutex[eServer]->unlock();
}

void Player::serverInfos(Network::TcpPacket* packet) {
    _attributesMutex[eServer]->lock();
    std::string name = _server->getName();
    _attributesMutex[eServer]->unlock();

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(Network::TcpProxy::InformationsGameGeneralResponse);
    *tcpPacket << name;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
}

void Player::listGame(Network::TcpPacket* packet) {
    sendGamesList();
}

void Player::playerList(Network::TcpPacket* packet) {
    uint32 gameId;

    *packet >> gameId;
    _attributesMutex[eServer]->lock();
    _server->listPlayers(gameId, this);
    _attributesMutex[eServer]->unlock();
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

void Player::quitGame(Network::TcpPacket* packet) {
    uint32 gameId;
    
    *packet >> gameId;
    _isReady = false;
    _server->quitGame(this, gameId);
}

void Player::sendGamesList(void) {
    _attributesMutex[eServer]->lock();
    std::map<uint32, Game*> const& games = _server->getGames();
    _attributesMutex[eServer]->unlock();
    
    std::list<Game*> newGamesList;
    for (std::map<uint32, Game*>::const_iterator it = games.begin(), end = games.end();
         it != end; ++it) {
        newGamesList.push_back(it->second);
    }
    
    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(Network::TcpProxy::InformationsGameListResponse);
    *tcpPacket << newGamesList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    
    _attributesMutex[eProxy]->lock();
    _proxy.sendPacket(toSend);
    _attributesMutex[eProxy]->unlock();
}

Network::APacket& operator<<(Network::APacket& packet, Player const& player) {
    packet << player.getId() << player.getName() << (char)player.isReady();
    return packet;
}