//
// Map.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 21:34:38 2013 Samuel Olivier
//

#include <fstream>

#include <Types.h>

#include "Map.h"

Map::Map() {
}

Map::~Map() {
}

bool	Map::load(std::string const& mapName) {
	std::ifstream	file(mapName.c_str(), std::ifstream::binary);
	uint32			nbr;

	file >> nbr;
	if (nbr != MapMagic) {
		_error = mapName + " is not a RType Map";
		file.close();
		return false;
	}
	file >> nbr;
	for (; nbr > 0 && file.good(); --nbr) {
		Object obj;
		int32	size;
		char	*data;

		file >> size;
		data = new char[size];
		file.read(data, size);
		obj.name.assign(data, size);
		delete []data;
		file >> obj.xStart;
		file >> size;
		data = new char[size];
		file.read(data, size);
		obj.params.bufcopy(data, size);
		delete []data;
		_objects.push_back(obj);
	}
	return true;
}

std::list<Map::Object> const&	Map::getObjects() const {
	return (_objects);
}

std::string const&				Map::getError() const {
	return (_error);
}