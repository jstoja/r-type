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
# include <map>

# include <Types.h>

# include "GameObject.h"
# include "Sprite.h"

class Map {
public:
	Map();
	~Map();

	static const uint32	MapMagic = 4242;
	struct Object {
		std::string	name;
		float32		xStart;
		ByteArray	params;
	};

	bool	load(std::string const& mapName);

	std::string const&			getError() const;
	std::list<Object> const&	getObjects() const;
	std::map<std::string, Sprite*> const&	getSprites() const;
	std::map<std::string, Texture*> const&	getTextures() const;
	std::string const&			getName() const;
	std::string const&			getFilename() const;
	float32						getSpeed() const;

private:
	bool					_getFilename(std::string const& filePath);
	bool					_checkMagic(std::ifstream& file);
	bool					_getName(std::ifstream& file);
	bool					_getSpeed(std::ifstream& file);
	bool					_loadSprites(std::ifstream& file);
	bool					_loadObject(std::ifstream& file);
	bool					_loadFrames(std::ifstream& file, Sprite *sprite);

	std::string				_error;
	std::list<Object>		_objects;
	std::map<std::string, Texture*>		_textures;
	std::map<std::string, Sprite*>		_sprites;
	std::string				_name;
	std::string				_filename;
	float32					_initialSpeed;
};

#endif