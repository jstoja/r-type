//
// IServerDelegate.cpp by Melvin Laplanche
// 01-12-13
//

#ifndef _ISERVERDELEGATE_H_
#define _ISERVERDELEGATE_H_

class IServerDelegate
{
public:
    virtual bool    createGame(Game* game, Player* player) = 0;
    virtual int     joinGame(std::string const& gameName, Player* player) = 0;
    virtual void    quitGame(uint32 gameId, Player* player);
};