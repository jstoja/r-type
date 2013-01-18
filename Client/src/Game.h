//
// Game.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 10:22:58 2013 Samuel Olivier
//

#ifndef _GAME_H_
# define _GAME_H_

# include <Object.h>
# include <Network/TcpPacket.h>

class Game : public Object {
public:
	Game(uint32 id);

	void				setName(std::string const& name);
	std::string const&	getName() const;

	void	setNbPlayer(uint32 nbPlayer);
	uint32	getNbPlayer() const;

	void	setNbSlot(uint32 nbSlot);
	uint32	getNbSlot() const;

	static Game*	newGame(Network::TcpPacket& packet);
private:
	std::string	_name;
	uint32		_nbPlayer;
	uint32		_nbSlot;
};

#endif