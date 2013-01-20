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
#include "Graphic/Renderer.h"
#include "Graphic/TextureManager.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Clock.h"


// Copy frame class, defined in Server
Frame::Frame(Vec2 const& p1, Vec2 const& p2)
: p1(p1), p2(p2) {
}

Network::APacket&		operator<<(Network::APacket & packet, Frame const& element) {
	return packet << element.p1 << element.p2;
}

// Global scene
Graphic::Scene scene;

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
        Graphic::Sprite* sprite = new Graphic::Sprite();
        sprite->setTexture(new Graphic::Texture(textureName));
        for (std::list<Frame>::const_iterator it = frames.begin(), end = frames.end(); it != end; ++it) {
            sprite->addFrame(Graphic::Sprite::Frame(it->p1, it->p2));
        }
        _graphicSprites[spriteName] = sprite;
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
    
    std::map<std::string, Graphic::Sprite*> _graphicSprites;

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

// Global map
Test map;

ByteArray	createBlockParams(Vec3 const& pos, Vec2 const& size, float32 rotation, std::string const& sprite, char frameIndex) {
	ByteArray	res;
	uint32		tmpSize = sprite.size();
    
    Graphic::Element* element = new Graphic::Element();
    element->setPosition(pos);
    element->setSize(size);
    element->setRotation(rotation);
    element->setSprite(map._graphicSprites[sprite]);
    element->setCurrentFrame(frameIndex);
    scene.addElement(element);

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
    
    Graphic::Scenery* scenery = new Graphic::Scenery();
    scenery->setTexture(map._graphicSprites[sprite]->getTexture());
    scenery->setSpeed(speed);
    scenery->setWidth(width);
    scenery->setRange(Vec2(0, xEnd));
    scenery->setDepth(depth);
    scenery->setOpacity(opacity);
    scene.addScenery(scenery);

	res.append((char*)&tmpSize, sizeof(tmpSize));
	res.append(sprite.c_str(), tmpSize);
	res.append((char*)&speed, sizeof(speed));
	res.append((char*)&width, sizeof(width));
	res.append((char*)&xEnd, sizeof(xEnd));
	res.append((char*)&depth, sizeof(depth));
	res.append((char*)&opacity, sizeof(opacity));
	return res;
}

Frame	createFromPosAndSize(Vec2 const& pos, Vec2 const& size) {
	return (Frame(pos, pos + size));
}

Frame	getFrame(float32 y, float32 width, float32 height) {
	static float32	previousX = 0;

	if (y < 0) {
		previousX = 0;
		return (Frame(Vec2(), Vec2()));
	}
	float32 now = previousX;
	previousX += width;
	return (createFromPosAndSize(Vec2(now, y), Vec2(width, height)));
}

Frame getFrame(std::list<Frame> & frames, uint32 id) {
	std::list<Frame>::iterator it = frames.begin();
	std::advance(it, id);
	return (*it);
}

class Loop : public Event::IListenerDelegate {
public:
    
    bool _close;
    
    Loop() : _close(false) {
        
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
        
        Clock clock;
        
        while (!_close) {
            scene.setViewportPosition(Vec2((float32)clock.getEllapsedTime()/1000, 0));
            Event::Manager::getInstance().processEvents();
            Graphic::Renderer::getInstance().render();
            Clock::sleep(33);
        }
        
    }
    
    void processEvent(Event::Event const& event) {
        if (event.type & Event::Close) {
            _close = true;
        }
    }
    
    ~Loop() {}
};

int	main(int ac, char **av) {
	Application::getInstance().init(ac, av);
    Application::getInstance().setRelativeResourcesPath("../../Server/Resources/Levels/Level_1/");
	std::string filename = "../../Server/Resources/Levels/Level_1/Level_1.map";
	std::string	name = "The Map";

	if (ac > 1)
		filename = av[0];
	std::list<Frame> framesFull, framesBlockDown, framesBlockUp;
	framesFull.push_back(Frame(Vec2(0, 0), Vec2(1, 1)));

	framesBlockDown.push_back(getFrame(0./3, 0.194, 1./3));
	framesBlockDown.push_back(getFrame(0./3, 0.2, 1./3));
	framesBlockDown.push_back(getFrame(0./3, 0.202, 1./3));
	framesBlockDown.push_back(getFrame(3, 0.202, 1.));
	framesBlockDown.push_back(getFrame(0./3, 0.202, 2./3));

    getFrame(-1, 0, 0);
    framesBlockUp.push_back(getFrame(1./3, 0.194, -1./3));
	framesBlockUp.push_back(getFrame(1./3, 0.2, -1./3));
	framesBlockUp.push_back(getFrame(1./3, 0.202, -1./3));
	framesBlockUp.push_back(getFrame(0, 0.202, -1.));
	framesBlockUp.push_back(getFrame(2./3, 0.202, -2./3));

    
	map.setName(name);
	map.setSpeed(0);
	map.addSprite("scenery1", "Images/background.png", framesFull);
	map.addSprite("scenery2", "Images/stars-deep.png", framesFull);
	map.addSprite("scenery3", "Images/stars-blue.png", framesFull);
	map.addSprite("scenery4", "Images/stars-red.png", framesFull);
	map.addSprite("scenery5", "Images/planets.png", framesFull);
	map.addSprite("blockDown", "Images/block-ship.png", framesBlockDown);
	map.addSprite("blockUp", "Images/block-ship.png", framesBlockUp);
	map.addObject("SceneryObject", 0, createSceneryParams("scenery1", 0, 16, 1000, 0.999, 1));
	map.addObject("SceneryObject", 0, createSceneryParams("scenery2", 0.2, 16, 1000, 0.998, 0.2));
	map.addObject("SceneryObject", 0, createSceneryParams("scenery3", 0.8, 16, 1000, 0.997, 1));
	map.addObject("SceneryObject", 0, createSceneryParams("scenery4", 1.2, 16, 1000, 0.996, 1));
	map.addObject("SceneryObject", 0, createSceneryParams("scenery5", 0.5, 16*3, 1000, 0.995, 0.8));
	float32 tmp1 = 0;
	float32 tmp2 = 0;
    for (int nbBlock = 0; nbBlock < 42; ++nbBlock) {
        uint32 idx = std::rand() % 5;
        Frame current = getFrame(framesBlockDown, idx);
        float32 width = (current.p2.x - current.p1.x) * 1.6 / 0.202,
        height = (current.p2.y - current.p1.y) * 0.4 / (1. / 3.);
        map.addObject("Block", 2, createBlockParams(Vec3(tmp1 + width / 2, height / 2, 0), Vec2(width, height), 0, "blockDown", idx));
        tmp1 += width;

        idx = std::rand() % 5;
        current = getFrame(framesBlockUp, idx);
        width = (current.p2.x - current.p1.x) * 1.6 / 0.202;
        height = (current.p1.y - current.p2.y) * 0.4 / (1. / 3.);
        map.addObject("Block", 2, createBlockParams(Vec3(tmp2 + width / 2, 9 - height / 2, 0), Vec2(width, height), 0, "blockUp", idx));
        tmp2 += width;
    }

	map.save(Application::getInstance().getRelativePath(filename));
    
    // Show the scene
    Graphic::Renderer::getInstance().init();
    Graphic::Renderer::getInstance().setScene(&scene);
    Graphic::TextureManager::getInstance().update();

    Loop loop;
	return (0);
}