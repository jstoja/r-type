//
// Map.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 21:32:31 2013 Samuel Olivier
//

#ifndef _MAP_H_
# define _MAP_H_

# include <string>
# include <sstream>
# include <list>

# include <Types.h>

# include "GameObject.h"

class Map {
public:
	Map();
	~Map();

	bool	load(std::string const& mapName);
	std::string const&	getError() const;

	static const uint32	MapMagic = 4242;
	struct Object {
		std::string	name;
		float32		xStart;
		ByteArray	params;
	};

	std::list<Object> const&	getObjects() const;

private:
	std::list<Object>	_objects;
	std::string				_error;
};

#endif