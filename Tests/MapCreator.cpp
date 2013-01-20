//
// MapCreator.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 21:24:42 2013 Samuel Olivier
//

#include <string>
#include <list>
#include <fstream>

#include <Application.h>
#include <Map.h>
#include <Types.h>
#include <Frame.h>

template<class T>
void	writeData(std::ofstream& file, T data) {
	file.write((char*)&data, sizeof(data));
}

class Test {
public:
	Test() {}
	~Test() {}

	void	setName(std::string const& name) {
		_name = name;
	}

	void	addSprite(std::string const& spriteName, std::string const& textureName, std::list<Frame> const& frames) {
		MapSprite add;
		add.spriteName = spriteName;
		add.textureName = textureName;
		add.frames = frames;
		_sprites.push_back(add);
	}

	void	addObject(std::string const& name, float32 xStart, ByteArray const& params) {
		Map::Object	add;
		add.name = name;
		add.xStart = xStart;
		add.params = params;
		_objects.push_back(add);
	}

	void	save(std::string const& filename) {
		std::ofstream	file(filename.c_str(), std::ofstream::binary);

		writeData<uint32>(file, Map::MapMagic);
		writeData<uint32>(file, _name.size());
		file.write(_name.c_str(), _name.size());
		writeData<float32>(file, _speed);
		writeData<uint32>(file, _sprites.size());
		for (std::list<MapSprite>::iterator it = _sprites.begin(); it != _sprites.end(); ++it) {
			writeData<uint32>(file, it->spriteName.size());
			file.write(it->spriteName.c_str(), it->spriteName.size());
			writeData<uint32>(file, it->textureName.size());
			file.write(it->textureName.c_str(), it->textureName.size());
			writeData<uint32>(file, it->frames.size());
			for (std::list<Frame>::iterator it1 = it->frames.begin(); it1 != it->frames.end(); ++it1) {
				writeData<float32>(file, it1->p1.x);
				writeData<float32>(file, it1->p1.y);
				writeData<float32>(file, it1->p2.x);
				writeData<float32>(file, it1->p2.y);
			}
		}
		writeData<uint32>(file, _objects.size());
		for (std::list<Map::Object>::iterator it = _objects.begin(); it != _objects.end(); ++it) {
			writeData<uint32>(file, it->name.size());
			file.write(it->name.c_str(), it->name.size());
			writeData<float32>(file, it->xStart);
			writeData<uint32>(file, it->params.getSize());
			file.write(it->params.getData(), it->params.getSize());
		}
		file.close();
	}

	void	setSpeed(float32 speed) {
		_speed = speed;
	}

private:
	struct MapSprite {
		std::string			spriteName;
		std::string			textureName;
		std::list<Frame>	frames;
	};
	std::string				_name;
	std::list<MapSprite>	_sprites;
	std::list<Map::Object>	_objects;
	float32					_speed;
};

ByteArray	createBlockParams(Vec3 const& pos, Vec2 const& size, float32 rotation, std::string const& sprite, char frameIndex) {
	ByteArray	res;
	uint32		tmpSize = sprite.size();

	res.append((char*)&pos, sizeof(pos));
	res.append((char*)&size, sizeof(size));
	res.append((char*)&rotation, sizeof(rotation));
	res.append((char*)&tmpSize, sizeof(tmpSize));
	res.append(sprite.c_str(), tmpSize);
	res.append(&frameIndex, sizeof(frameIndex));
	return res;
}

ByteArray	createSceneryParams(std::string const& sprite, float32 speed, float32 width, float32 xEnd, float32 depth, float32 opacity) {
	ByteArray	res;
	uint32		tmpSize = sprite.size();

	res.append((char*)&tmpSize, sizeof(tmpSize));
	res.append(sprite.c_str(), tmpSize);
	res.append((char*)&speed, sizeof(speed));
	res.append((char*)&width, sizeof(width));
	res.append((char*)&xEnd, sizeof(xEnd));
	res.append((char*)&depth, sizeof(depth));
	res.append((char*)&opacity, sizeof(opacity));
	return res;
}

int	main(int ac, char **av) {
	Application::getInstance().init(ac, av);
	std::string filename = "level.map";
	std::string	name = "The Map";

	if (ac > 1)
		filename = av[0];
	std::list<Frame> frames;
	frames.push_back(Frame(Vec2(0, 0), Vec2(500, 500)));

	Test	map;
	map.setName(name);
	map.setSpeed(0.2);
	map.addSprite("scenery1", "Images/Scenery1.png", frames);
	map.addSprite("block", "Images/block.png", frames);
	map.addObject("Scenery", 0, createSceneryParams("scenery1", 0.1, 16, 1000, 0.9, 1));
	map.addObject("Block", 0, createBlockParams(Vec3(8, 4.5, 0), Vec2(4, 3), 0, "block", 0));
	map.save(Application::getInstance().getRelativePath(filename));
	return (0);
}