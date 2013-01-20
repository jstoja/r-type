//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#ifndef _GAME_H_
# define _GAME_H_

# include <string>
# include <list>
# include <map>

# include <OS.h>
# include <Object.h>
# include <Network/Proxy.hpp>
# include <Network/TcpPacket.h>
# include <Network/UdpPacket.h>
# include <Network/UdpSocket.h>
# include <Network/CriticalPacket.h>
# include <Threading/ThreadPool.hpp>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"
# include <IGame.h>

# include "GraphicScene.h"
# include "GraphicElement.h"
# include "PhysicScene.h"
# include "PhysicElement.h"
# include "Texture.h"
# include "Sound.h"
# include "Scenery.h"
# include "Map.h"
# include "Viewport.h"

class Player;
class GameObject;

class Game : public IGame, public Object, public Network::IProxyDelegate<Network::UdpPacket>
{
public:
    enum State {Stopped, Waiting, Started};

    Game(Network::TcpPacket* packet=NULL);
    virtual ~Game();

    std::string const&      getName(void) const;
    void                    setName(std::string const& name);
    Player const*           getReferee(void) const;
    void                    setReferee(Player*);
    State					getState(void) const;
    uint32                  getNbPlayers(void) const;
    uint32                  getNbSlots(void) const;
    void                    setNbSlots(uint32 slots);


    void    packetInProgress(uint32 code, float32 progress) {}
    void	join(Player* player);
    bool    hasPlayer(Player* player) const;
    bool	canJoin(Player* player=NULL) const;
    bool    quit(Player* player);
    void    playerReady(Player* player);
    void	sendInfo(Player* player);
    void	start(void);
    void	update();
    void    sendPlayerList(Player* player);

    void    connectionClosed(Network::Proxy<Network::UdpPacket>*);
    void    packetSent(Network::UdpPacket const* packet);
    void    packetReceived(Network::UdpPacket* packet);

    virtual void                addGraphicElement(IGraphicElement* element);
    virtual IGraphicElement*    createGraphicElement() const;
	virtual ITexture*			createTexture(std::string const& filename, std::string const& pluginName);
	virtual ISprite*			createSprite(ITexture *texture);
	virtual ISprite*			getLevelSprite(std::string const& name);

	virtual void	addPhysicElement(IPhysicElement* element);
	virtual IPhysicElement*	createPhysicElement() const;

	virtual ISound*				loadSound(std::string const& name, std::string const& pluginName);
	virtual ISound*				loadSound(std::string const& name);

	virtual IScenery*			addScenery();

	virtual IViewport*			getViewport() const;

	void						_loadMap(std::string const& fileName);
    void                        sendResources(Network::TcpPacket &packet);

    virtual uint64              getEllapsedTime() const;

    void updatePlayerDirection(Network::UdpPacket*);
    void playerShoot(Network::UdpPacket*);
    void physicCollision(Network::UdpPacket*);

    typedef void (Game::* commandPointer)(Network::UdpPacket*);

private:
    void                        _udpHandler(void);
    void                        _sendTime(Player* player);
    void                        _sendGraphicElements(Player* player);
    void                        _sendPhysicElements(Player* player);
    void                        _sendSound(Player* player);

    Threading::Mutex*                           _attributesMutex;
	std::vector<Player*>                        _players;
	uint32                                      _nbSlots;
	std::string                                 _name;
	Map                                         _currentLevel;
	std::list<GameObject*>                      _objects;
	std::list<Texture*>                         _gameTextures;
	std::map<std::string, Sprite*>	            _levelSprites;
	std::list<Sprite*>				            _gameSprites;
	std::list<Scenery*>				            _gameSceneries;
	std::list<Sound*>				            _gameSounds;
	GraphicScene					            _graphicScene;
	PhysicScene						            _physicScene;
	Threading::ThreadPool*			            _updatePool;
    State                                       _state;
    Player*                                     _referee;
	Clock							            _clock;
	Clock							            _gameClock;
	Viewport*						            _viewport;
    Network::Proxy<Network::UdpPacket>*         _proxy;
    Network::UdpSocket*                         _udpSocket;

    std::map<int, commandPointer>         _commands;

#ifdef OS_MAC
	static const int					_updateThreadNumber = 7;
#else
	static const int					_updateThreadNumber = 3;
#endif
};

Network::APacket&       operator<<(Network::APacket& packet, Game const& game);

#endif
