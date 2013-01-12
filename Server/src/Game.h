//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#ifndef _GAME_H_
# define _GAME_H_
# include <string>
# include "IGame.h"
# include "Object.h"
# include "Network/TcpPacket.h"

class Player;

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
    virtual IGraphicElement*    createGraphicElement();

private:
  std::vector<Player*>  _players;
  uint32                _nbSlots;
  std::string           _name;
};

#endif