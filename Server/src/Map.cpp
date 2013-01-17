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
#include <Application.h>

#include "Map.h"
#include "Texture.h"

Map::Map() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        _attributesMutex[i] = new Threading::Mutex();
    }
}

Map::~Map() {
    for (uint32 i = 0; i < eLastAttribute; ++i) {
        delete _attributesMutex[i];
    }
}

bool	Map::load(std::string const& mapName) {
	std::ifstream	file(mapName.c_str(), std::ifstream::binary);
    
	if (file.is_open() == false) {
        _attributesMutex[eError]->lock();
		_error = "Cannot open " + mapName;
        _attributesMutex[eError]->unlock();
		return false;
	}
	if (!_getFilename(mapName) || !_checkMagic(file) || !_getName(file) || !_loadSprites(file) || !_loadObject(file)) {
		file.close();
		return false;
	}
	return true;
}

std::string const&				Map::getError() const {
    Threading::MutexLocker  locker(_attributesMutex[eError]);
	return (_error);
}

std::list<Map::Object> const&	Map::getObjects() const {
    Threading::MutexLocker  locker(_attributesMutex[eObjects]);
	return (_objects);
}

std::map<std::string, Sprite*> const&	Map::getSprites() const {
    Threading::MutexLocker  locker(_attributesMutex[eSprites]);
	return (_sprites);
}

std::map<std::string, Texture*> const&	Map::getTextures() const {
    Threading::MutexLocker  locker(_attributesMutex[eTextures]);
	return (_textures);
}

std::string const&				Map::getName() const {
    Threading::MutexLocker  locker(_attributesMutex[eName]);
	return (_name);
}

std::string const&				Map::getFilename() const {
    Threading::MutexLocker  locker(_attributesMutex[eFilename]);
	return (_filename);
}

bool	Map::_getFilename(std::string const& filePath) {
    _attributesMutex[eApplication]->lock();
	size_t idx = filePath.find_last_of(Application::getInstance().getDirectorySeparator());
	if (idx != std::string::npos)
		++idx;
    _attributesMutex[eApplication]->unlock();
    
    _attributesMutex[eFilename]->lock();
	_filename = filePath.substr(idx);
	_filename = _filename.substr(0, _filename.find_last_of(".lvl"));
    _attributesMutex[eFilename]->unlock();
	return (true);
}

bool	Map::_checkMagic(std::ifstream& file) {
	uint32			nbr;

	file.read((char*)&nbr, sizeof(nbr));
	if (nbr != MapMagic) {
		_error = _filename + " is not a RType Map";
		file.close();
		return false;
	}
	return (true);
}

bool	Map::_getName(std::ifstream& file) {
	uint32	size;
	char	*data;

	file.read((char*)&size, sizeof(size));
	data = new char[size];
	file.read(data, size);
    _attributesMutex[eName]->lock();
	_name.assign(data, size);
    _attributesMutex[eName]->unlock();
	delete []data;
	return (true);
}

bool	Map::_loadSprites(std::ifstream& file) {
	uint32	nbr;

	file.read((char*)&nbr, sizeof(nbr));
    Threading::MutexLocker locker(_attributesMutex[eApplication]);
    Threading::MutexLocker locker1(_attributesMutex[eTextures]);
    Threading::MutexLocker locker2(_attributesMutex[eSprites]);
    Threading::MutexLocker locker3(_attributesMutex[eFilename]);

	for (; nbr > 0 && file.good(); --nbr) {
		std::string	spriteName, imageName;
		uint32	size;
		char	*data;

		file.read((char*)&size, sizeof(size));
		data = new char[size];
		file.read(data, size);
		spriteName.assign(data, size);
		delete []data;
		file.read((char*)&size, sizeof(size));
		data = new char[size];
		file.read(data, size);
		imageName.assign(data, size);
		delete []data;
		Texture*	texture = _textures[imageName];
		if (texture == NULL) {
			texture = new Texture(std::string("Levels") +
			App.getDirectorySeparator() + std::string(_filename) +
			App.getDirectorySeparator() + std::string(imageName));
			_textures[imageName] = texture;
		}
		if (_sprites[spriteName] != NULL) {
			_error = "Multiple Definition of Sprite " + spriteName;
			return false;
		}
		Sprite*		sprite = new Sprite(texture);
		_sprites[spriteName] = sprite;
		if (_loadFrames(file, sprite) == false)
			return false;
	}
	return true;
}

bool	Map::_loadFrames(std::ifstream& file, Sprite *sprite) {
	uint32	nbr;

	file.read((char*)&nbr, sizeof(nbr));
	for (; nbr > 0 && file.good(); --nbr) {
		Vec2	p1, p2;
		file.read((char*)&p1, sizeof(p1));
		file.read((char*)&p2, sizeof(p2));
		sprite->addFrame(p1, p2);
	}
	return true;
}

bool	Map::_loadObject(std::ifstream& file) {
	uint32	nbr;

    _attributesMutex[eObjects]->lock();
	file.read((char*)&nbr, sizeof(nbr));
	for (; nbr > 0 && file.good(); --nbr) {
		Object obj;
		int32	size;
		char	*data;

		file.read((char*)&size, sizeof(size));
		data = new char[size];
		file.read(data, size);
		obj.name.assign(data, size);
		delete []data;
		file.read((char*)&obj.xStart, sizeof(obj.xStart));
		file.read((char*)&size, sizeof(size));
		data = new char[size];
		file.read(data, size);
		obj.params.bufcopy(data, size);
		delete []data;
		_objects.push_back(obj);
	}
    _attributesMutex[eObjects]->unlock();
	return (true);
}