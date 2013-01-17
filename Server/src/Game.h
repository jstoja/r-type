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
# include <Network/TcpPacket.h>
# include <Network/UdpPacket.h>
# include <Threading/ThreadPool.hpp>
# include <IGame.h>

# include "GraphicScene.h"
# include "GraphicElement.h"
# include "PhysicScene.h"
# include "PhysicElement.h"
# include "Texture.h"
# include "Sound.h"
# include "Scenery.h"
# include "Map.h"

class Player;
class GameObject;

class Game : public IGame, public Object
{
public:
    enum State {STOPPED, WAITING, STARTED};

    Game(Network::TcpPacket* packet);
    ~Game();

    std::string const&      getName(void) const;
    State                   getState(void) const;
    uint32                  getNbPlayers(void) const;
    uint32                  getNbSlots(void) const;

    void     join(Player* player);
    bool     canJoin();
    void     quit(Player* player);
    void     playerReady(Player* player);
    void     start(void);
    void     udpHandler(void);

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

	void						loadMap(std::string const& fileName);
    void                        sendResources(Network::TcpPacket &packet);
private:
	void						_update();
    void                        _sendSound(void);
    void                        _sendGraphicElements(void);
    void                        _sendPhysicElements(void);

	std::vector<Player*>            _players;
	uint32                          _nbSlots;
	std::string                     _name;
	Map                             _currentLevel;
	std::list<GameObject*>          _objects;
	std::list<Texture*>             _gameTextures;
	std::map<std::string, Sprite*>	_levelSprites;
	std::list<Sprite*>				_gameSprites;
	std::list<Scenery*>				_gameSceneries;
	std::list<Sound*>				_gameSounds;
	GraphicScene					_graphicScene;
	PhysicScene						_physicScene;
	Threading::ThreadPool*			_updatePool;
    State                           _state;

#ifdef OS_MAC
	static const int					_updateThreadNumber = 7;
#else
	static const int					_updateThreadNumber = 3;
#endif
};

Network::APacket&       operator<<(Network::APacket& packet, Game const& game);

#endif