//
// Player.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 10:53:20 2013 Samuel Olivier
//

#ifndef _PLAYER_H_
# define _PLAYER_H_

# include <Object.h>
# include <Network/TcpPacket.h>

class Player : public Object {
public:
	Player(uint32 id);

	void				setName(std::string const& name);
	std::string const&	getName() const;

	void	setNbPlayer(uint32 nbPlayer);
	uint32	getNbPlayer() const;

	void	setIsReady(bool nbSlot);
	bool	isReady() const;

	static Player*	newPlayer(Network::TcpPacket& packet);

private:
	std::string	_name;
	bool		_isReady;
};

#endif