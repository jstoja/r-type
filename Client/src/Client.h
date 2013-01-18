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
# include "UserInterface.h"
# include "Network/Proxy.hpp"
# include "Network/TcpSocket.h"
# include "Network/TcpPacket.h"

class Client :  public IUserInterfaceDelegate, public Network::IProxyDelegate<Network::TcpPacket>, public Network::ISocketDelegate {
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
    
    uint32  getFramerateLimit(void) const;
    
    // User interface delegate methods
    Graphic::Scene* getScene(void);
    virtual void    loginCompleted(std::string const& login,
                                   std::string const& ipAdress,
                                   std::string const& port);
    
    // Socket delegate
	void connectionFinished(Network::ASocket*, bool success);
                    
    // Network proxy delegate methods
    void packetReceived(Network::TcpPacket* packet);
    void packetSent(Network::TcpPacket const* packet);
    void connectionClosed(Network::Proxy<Network::TcpPacket>* packet);
    
    // Protocol commands
    void connectionResponse(Network::TcpPacket* packet);
    void receiveGeneralInformations(Network::TcpPacket* packet);
    void receiveGameList(Network::TcpPacket* packet);
    
    typedef void (Client::* commandPointer)(Network::TcpPacket*);
    
    private:
    Graphic::Scene  _scene;
    uint32          _framerateLimit;
    Clock           _time;
    UserInterface*  _ui;
    
    Network::TcpSocket*                 _tcpSocket;
    Network::Proxy<Network::TcpPacket>* _proxy;
    std::map<int, commandPointer>       _commands;

    std::string                         _login;
    uint32                              _userId;
};

#endif
