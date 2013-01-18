//
// Client.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sun Dec 23 13:59:18 2012 loick michard
//

#include "Client.h"

#include "Graphic/Renderer.h"
#include "Event/Manager.h"
#include "Application.h"

#include "Graphic/Image.h"

Client::Client(void) :
_scene(), _framerateLimit(30), _time(), _ui(), _tcpSocket(NULL), _proxy(NULL),
_commands(), _userId(0) {
    
    _commands[Network::Proxy<Network::TcpPacket>::AuthenficitationConnectionSuccess] = &Client::connectionResponse;
    
    Graphic::Renderer::getInstance().init();
    Graphic::Renderer::getInstance().setScene(&_scene);
    
    // Adapt the scene viewport to the window aspect
    Vec2 viewport = _scene.getViewport();
    Vec2 screen = Graphic::Renderer::getInstance().getViewportSize();
    
    viewport.x = viewport.y * (screen.x / screen.y);
    _scene.setViewport(viewport);
    
    // Create the ui
    _ui = new UserInterface(this);
    
    //loginCompleted("aurao", "127.0.0.1", "4242");

    mainLoop();
}

Client::~Client(void) {
    delete _tcpSocket;
    delete _proxy;
}

void Client::mainLoop(void) {
#ifndef OS_IOS
    while (true) {
        Clock frameClock;
        
        update();
        render();
        
        // Framerate limitation
        uint64 frameTime = 1000 / _framerateLimit;
        uint64 ellapsedTime = frameClock.getEllapsedTime();
        if (ellapsedTime < frameTime) {
            Clock::sleep(frameTime - ellapsedTime);
        }
        frameClock.reset();
    }
#endif
}

void Client::update(void) {
    Event::Manager::getInstance().processEvents();
    _ui->update();
}

void Client::render(void) {
    Graphic::Renderer::getInstance().render();
}

uint32 Client::getFramerateLimit(void) const {
    return _framerateLimit;
}

Graphic::Scene* Client::getScene(void) {
    return &_scene;
}

void Client::loginCompleted(std::string const& login, std::string const& ipAdress,
                            std::string const& port) {
    delete _tcpSocket;
    delete _proxy;
    _proxy = NULL;
    _tcpSocket = new Network::TcpSocket();
	_tcpSocket->connect(ipAdress, std::atoi(port.c_str()));
    //if (_tcpSocket->connect(ipAdress, std::atoi(port.c_str()))) {
    //    Log("Connected to server");
    //    _proxy = new Network::Proxy<Network::TcpPacket>(_tcpSocket, this);
    //    Network::TcpPacket* packet = new Network::TcpPacket();
    //    packet->setCode(Network::Proxy<Network::TcpPacket>::AuthenficitationConnection);
    //    *packet << login;
    //    _proxy->sendPacket(packet);
    //} else {
    //    Log("Connection failed");
    //}
}

void Client::packetReceived(Network::TcpPacket* packet) {
    uint32 code, size;
    
    *packet >> code >> size;
    std::map<int, commandPointer>::iterator it = _commands.find(code & 0xFFFFFF00);
    if (it != _commands.end())
        (this->*(it->second))(packet);
    else
        Log("Received unknown command " << code);
    delete packet;
}

void Client::connectionResponse(Network::TcpPacket* packet) {
    if ((packet->getCode() & 0xFF) == 1) {
        Log("Connection error");
    } else {
        uint32 id;
        *packet >> id;
        
        _userId = id;
        _ui->goToMenu("Game");
    }
}

void Client::packetSent(Network::TcpPacket const* packet) {
    Log("Packet sent");
}

void Client::connectionClosed(Network::Proxy<Network::TcpPacket>* packet) {
    Log("Connection closed");
}

void Client::connectionFinished(Network::Proxy<Network::TcpPacket>* packet, bool success) {

}