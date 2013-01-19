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
# include "Resource.h"
# include "Graphic/Scene.h"
# include "Graphic/Texture.h"
# include "Graphic/Element.h"
# include "Graphic/Scenery.h"
# include "Sound/Sound.h"

class GameController : public Event::IListenerDelegate {

public:
    
    GameController(Game* game, Graphic::Scene* scene);
    virtual ~GameController(void);
    
    // Event listener delegate methods
    virtual void processEvent(Event::Event const& event);
    
    // Game creation
    void                        receiveResources(Network::TcpPacket* packet);
	static Resource*			createResource(Network::TcpPacket& packet);
	static Graphic::Texture*	createTexture(Network::TcpPacket& packet);
	static Graphic::Sprite*		createSprite(Network::TcpPacket& packet);
	static Graphic::Element*	createGraphicElement(Network::TcpPacket& packet);
	static Graphic::Scenery*	createScenery(Network::TcpPacket& packet);
	static Sound::Sound*		createSound(Network::TcpPacket& packet);
    
    void launchGame(void);
    void clearGame(void);

private:
    Game*                               _game;
    Graphic::Scene*                     _scene;
    Event::Listener*                    _eventListener;
	std::list<Resource*>				_resources;
	std::list<Graphic::Texture*>		_textures;
	std::list<Graphic::Sprite*>			_sprites;
	std::list<Graphic::Element*>		_elements;
	std::list<Graphic::Scenery*>		_sceneries;
	std::list<Sound::Sound*>			_sounds;
};

#endif /* defined(__R_Type__GameController__) */
