//
// IServerDelegate.cpp by Melvin Laplanche
// 01-12-13
//

#ifndef _ISERVERDELEGATE_H_
#define _ISERVERDELEGATE_H_

class Game;
class Player;

# include <map>

class IServerDelegate
{
public:
    virtual std::map<uint32, Game*> const&  getGames(void) = 0;
    virtual bool                            createGame(Game* game, Player* player) = 0;
    virtual int                             joinGame(uint32 gameId, Player* player) = 0;
    virtual void                            quitGame(Player* player) = 0;
    virtual void                            sendResources(uint32 gameId, Player* player) = 0;
    virtual void                            playerReady(uint32 gameId, Player* player) = 0;
    virtual void                            gameStart(uint32 gameId) = 0;
    virtual void                            sendGameInfo(uint32 gameId, Player* player) = 0;
};

#endif