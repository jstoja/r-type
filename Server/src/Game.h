//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#ifndef _GAME_H_
# define _GAME_H_
# include <string>
# include "Commons/IGame.h"
#include "Commons/Object.h"
# include "Network/TcpServer.h"

class Game : public IGame, public Object
{
public:
    Game(NNetwork::TcpPacket* packet);
    ~Game();

    std::string const&     getName(void);

    virtual addPhysicElement();
    virtual addGraphicElement();
    virtual playSound();
    virtual loadRessource();

    bool     join(Player* player);
    bool     canjoin();
    bool     quit(Player* player);

private:
  std::vector<Player*>  _players;
  int                   _nbSlots;
  std::string           _name;
};

#endif