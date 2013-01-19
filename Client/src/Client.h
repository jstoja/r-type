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

# include "Graphic/Scene.h"
# include "Clock.h"
# include "Event/Listener.h"
# include "UserInterface.h"
# include "GameController.h"
# include "Network/Proxy.hpp"
# include "Network/TcpSocket.h"
# include "Network/TcpPacket.h"
# include "Network/UdpSocket.h"
# include "Network/UdpPacket.h"
# include "Game.h"

class Client : public Event::IListenerDelegate, public IUserInterfaceDelegate, public Network::IProxyDelegate<Network::TcpPacket>, public Network::ISocketDelegate {
public:
    
    Client(void);
    virtual ~Client(void);
    
    //! Main loop of the application
    /*!
     The main loop call the update() and render() methods and limit the framerate
     of the application. On iOS, this functions does nothing, cause the mainloop
     is handled by the iOS framework.
     */
    void mainLoop(void);
    
    void update(void);
    void render(void);
    
    // Event listener delegate methods
    virtual void processEvent(Event::Event const& event);
    
    uint32  getFramerateLimit(void) const;
    
    // User interface delegate methods
    Graphic::Scene* getScene(void);
    virtual void    loginCompleted(std::string const& login,
                                   std::string const& ipAdress,
                                   std::string const& port);
    virtual void    newGameCompleted(std::string const& name,
                                     uint32 nbPlayers);
    virtual void    gameSelected(uint32 gameIndex);
    virtual void    playerReady();
    virtual void    leavedGameList(void);
    virtual void    leavedGame(void);
                        
    // Network TCP proxy delegate methods
    void packetReceived(Network::TcpPacket* packet);
    void packetSent(Network::TcpPacket const* packet);
    void connectionClosed(Network::Proxy<Network::TcpPacket>* proxy);
	void packetInProgress(uint32 code, float32 progress);

    // Protocol commands
    void connectionResponse(Network::TcpPacket* packet);
    void receiveGeneralInformations(Network::TcpPacket* packet);
    void receiveGameList(Network::TcpPacket* packet);
    void gameCreatedResponse(Network::TcpPacket* packet);
    void gameJoinResponse(Network::TcpPacket* packet);
    void receiveResources(Network::TcpPacket* packet);
    void receivePlayerList(Network::TcpPacket* packet);
    void receiveNewPlayer(Network::TcpPacket* packet);
	void receivePlayerReady(Network::TcpPacket* packet);
	void startGame(Network::TcpPacket* packet);
    
    // Socket delegate
	void connectionFinished(Network::ASocket*, bool success);

    typedef void (Client::* commandPointer)(Network::TcpPacket*);
    
private:
	void	_initGame(Game* game);
	void	_clearGame();

    bool                _close;
	Graphic::Scene      _scene;
    uint32              _framerateLimit;
    Clock               _time;
    Event::Listener*    _eventListener;
    UserInterface*      _ui;
    
    Network::TcpSocket*                 _tcpSocket;
    Network::TcpProxy*                  _proxy;
    
    std::map<int, commandPointer>       _commands;

    std::string                         _login;
    uint32                              _userId;
    std::list<Game*>                    _games;
	Game*								_currentGame;
    GameController*                     _gameController;
};

#endif
