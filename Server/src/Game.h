//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#ifndef _GAME_H_
# define _GAME_H_

# include <string>
# include <list>

# include "GraphicElement.h"

# include <Object.h>
# include <Network/TcpPacket.h>
# include <Network/UdpPacket.h>

# include "IGame.h"

class Player;
class GameObject;

class Game : public IGame, public Object
{
public:
    Game(Network::TcpPacket* packet);
    ~Game();

    std::string const&     getName(void);

    void     join(Player* player);
    bool     canJoin();
    void     quit(Player* player);

    virtual void                addGraphicElement(IGraphicElement* element);
    virtual IGraphicElement*    createGraphicElement() const;
	virtual ITexture*			createTexture(std::string const& filename, std::string const& pluginName) const;
	virtual ISprite*			createSprite(ITexture *texture) const;
	void						loadMap(std::string const& fileName);

private:
	void						_sendGraphicElements(Network::UdpPacket &packet);

	std::vector<Player*>  _players;
	uint32                _nbSlots;
	std::string           _name;
	std::list<GameObject*>		_objects;
	std::list<GraphicElement*>	_graphicElements;
};

#endif