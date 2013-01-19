//
//  GameController.h
//  R-Type
//
//  Created by Gael du Plessix on 19/01/13.
//
//

#ifndef __R_Type__GameController__
# define __R_Type__GameController__

# include "Game.h"
# include "Event/Listener.h"
# include "Event/IListenerDelegate.h"
# include "Network/TcpPacket.h"
# include "Network/Proxy.hpp"
# include "Network/UdpSocket.h"
# include "Network/UdpPacket.h"
# include "Resource.h"
# include "Graphic/Scene.h"
# include "Graphic/Texture.h"
# include "Graphic/Element.h"
# include "Graphic/Scenery.h"
# include "Sound/Sound.h"

class GameController : public Event::IListenerDelegate, public Network::IProxyDelegate<Network::UdpPacket> {

public:
    
    GameController(Game* game, Graphic::Scene* scene);
    virtual ~GameController(void);
    
    // Event listener delegate methods
    virtual void processEvent(Event::Event const& event);
    
    // Network UDP proxy delegate methods
    void packetReceived(Network::UdpPacket* packet);
    void packetSent(Network::UdpPacket const* packet);
    void connectionClosed(Network::Proxy<Network::UdpPacket>* proxy);
	void packetInProgress(uint32 code, float32 progress);
    
    // Game creation
    void                        receiveResources(Network::TcpPacket* packet);
	static Resource*			createResource(Network::TcpPacket& packet);
	static Graphic::Texture*	createTexture(Network::TcpPacket& packet);
	static Graphic::Sprite*		createSprite(Network::TcpPacket& packet);
	static Graphic::Element*	createGraphicElement(Network::TcpPacket& packet);
	static Graphic::Scenery*	createScenery(Network::TcpPacket& packet);
	static Sound::Sound*		createSound(Network::TcpPacket& packet);
    
    // Game actions
    void launchGame(void);
    void clearGame(void);
    void update(void);
    
    // Getters
    bool    gameLaunched(void) const;
    uint8   getUdpSocketPort(void) const;

private:
    Game*                               _game;
    bool                                _gameLaunched;
    Graphic::Scene*                     _scene;
    Event::Listener*                    _eventListener;
    Network::UdpSocket*                 _udpSocket;
    Network::UdpProxy*                  _udpProxy;
	std::list<Resource*>				_resources;
	std::list<Graphic::Texture*>		_textures;
	std::list<Graphic::Sprite*>			_sprites;
	std::list<Graphic::Element*>		_elements;
	std::list<Graphic::Scenery*>		_sceneries;
	std::list<Sound::Sound*>			_sounds;
};

#endif /* defined(__R_Type__GameController__) */
