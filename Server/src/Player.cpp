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

Player::Player(Network::TcpSocket* socket, IServerDelegate* server) :
_attributesMutex() ,_isReady(false), _name(), _socket(socket),
_proxy(socket, this), _server(server), _commands(), _isReferee(false),
_speed(0, 0), _position(16.0/2, 9.0/2) {

    _attributesMutex.resize(eLastAttribute);
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }

    Log("New Player " << socket->getRemoteAddress().getString());

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
    Threading::MutexLocker locker(_attributesMutex[eCommands]);
    std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
    if (it != _commands.end())
        (this->*(it->second))(packet);
    else {
        Log("Received unknown command 0x" << std::setfill('0') << std::setw(8) << std::hex << code);
    }
    delete packet;
}

bool Player::isReady(void) const {
    Threading::MutexLocker locker(_attributesMutex[eIsReady]);
    return _isReady;
}

std::string const& Player::getName(void) const {
    Threading::MutexLocker locker(_attributesMutex[eName]);
    return _name;
}

uint16              Player::getPort(void) const {
    Threading::MutexLocker locker(_attributesMutex[ePort]);
    return _port;
}

Network::HostAddress Player::getAddress(void) const {
    Threading::MutexLocker locker(_attributesMutex[eSocket]);
    return _socket->getRemoteAddress();
}

void Player::packetSent(Network::TcpPacket const* packet) {
    delete packet;
}

void Player::connectionClosed(Network::Proxy<Network::TcpPacket>*) {
    //Threading::MutexLocker locker(_attributesMutex[eServer]);
    _server->quitServer(this);
}

void Player::connection(Network::TcpPacket* packet) {
    std::string name;
    *packet >> name;
    Log("Connection with login " << name << ", id: " << getId());

    uint32 code = Network::TcpProxy::AuthenficitationConnectionSuccess;
    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    if (_server->canAddPlayer(name)) {
        Threading::MutexLocker lockerName(_attributesMutex[eName]);
        _name = name;
    } else {
        code = Network::TcpProxy::AuthenficitationConnectionIncorrectLogin;
    }
    lockerServer.unlock();
    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(code);
    *tcpPacket << (uint32)getId();
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
    lockerServer.relock();
}

void  Player::sendPacket(Network::Proxy<Network::TcpPacket>::ToSend const& toSend) {
    Threading::MutexLocker locker(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
}

void Player::createGame(Network::TcpPacket* packet) {
    Game *game = new Game(packet);

    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    bool gameCreated = _server->createGame(game, this);
    lockerServer.unlock();

    if (gameCreated == false) {
        delete game;
    }

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(gameCreated ? Network::TcpProxy::GameCreatedSuccess
                       : Network::TcpProxy::GameCreatedBadName);
    if (gameCreated)
        *tcpPacket << *game;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);
    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
    lockerProxy.unlock();
    // Send game infos
    if (gameCreated) {
        lockerServer.relock();
        _server->sendResources(game->getId(), this);
        _server->sendGameInfo(game->getId(), this);
        lockerServer.unlock();
    }
    lockerServer.relock();
    lockerProxy.relock();
}

void Player::joinGame(Network::TcpPacket* packet) {
    uint32 id;

    *packet >> id;

    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    int code = _server->joinGame(id, this);
    lockerServer.unlock();

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(code);
    *tcpPacket << id;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
    lockerProxy.unlock();

    if (code == Network::TcpProxy::GameJoinSuccess) {
        lockerServer.relock();
        _server->sendResources(id, this);
        _server->sendGameInfo(id, this);
        lockerServer.unlock();
    }
    lockerServer.relock();
    lockerProxy.relock();
}

void Player::serverInfos(Network::TcpPacket* packet) {
    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    std::string name = _server->getName();
    lockerServer.unlock();

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(Network::TcpProxy::InformationsGameGeneralResponse);
    *tcpPacket << name;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
    lockerServer.relock();
}

void Player::listGame(Network::TcpPacket* packet) {
    sendGamesList();
}

void Player::playerList(Network::TcpPacket* packet) {
    uint32 gameId;

    *packet >> gameId;
    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    _server->listPlayers(gameId, this);
}

void Player::readyToStart(Network::TcpPacket* packet) {
    uint32 gameId;
    uint16 port;

    *packet >> gameId;
    *packet >> port;
    Threading::MutexLocker lockePort(_attributesMutex[ePort]);
    _port = port;
    lockePort.unlock();

    Log("Port: " << port);

    Threading::MutexLocker lockerReady(_attributesMutex[eIsReady]);
    _isReady = true;
    lockerReady.unlock();

    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    _server->playerReady(gameId, this);
    lockerReady.relock();
    lockePort.relock();
}

void Player::quitGame(Network::TcpPacket* packet) {
    uint32 gameId;

    *packet >> gameId;
    Threading::MutexLocker lockerReady(_attributesMutex[eIsReady]);
    _isReady = false;
    lockerReady.unlock();

    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    _server->quitGame(this, gameId);
    lockerReady.relock();
}

void Player::sendGamesList(void) {
    Threading::MutexLocker lockerServer(_attributesMutex[eServer]);
    std::map<uint32, Game*> const& games = _server->getGames();
    lockerServer.unlock();
    std::list<Game*> newGamesList;
    for (std::map<uint32, Game*>::const_iterator it = games.begin(), end = games.end();
         it != end; ++it) {
        newGamesList.push_back(it->second);
    }

    Network::TcpPacket *tcpPacket = new Network::TcpPacket();
    tcpPacket->setCode(Network::TcpProxy::InformationsGameListResponse);
    *tcpPacket << newGamesList;
    Network::Proxy<Network::TcpPacket>::ToSend toSend(tcpPacket, Network::HostAddress::AnyAddress, 0);

    Threading::MutexLocker lockerProxy(_attributesMutex[eProxy]);
    _proxy.sendPacket(toSend);
    lockerServer.relock();
}

Network::APacket& operator<<(Network::APacket& packet, Player const& player) {
    packet << player.getId() << player.getName() << (char)player.isReady();
    return packet;
}

void Player::update(uint32 elapsedTime) {
    _position = _position + _speed * ((float32)elapsedTime/1000.0) * 4;
}

void Player::updateSpeed(const Vec2& speed) {
  _speed = speed;
  _speed.normalize();
}

Vec2 const& Player::getPosition(void) const {
    return _position;
}