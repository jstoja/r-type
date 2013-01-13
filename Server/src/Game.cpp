//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#include <algorithm>

#include <Application.h>
#include <Exception.h>

#include "Game.h"
#include "GraphicElement.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Map.h"

Game::Game(Network::TcpPacket* packet) {
    *packet >> _name;
    *packet >> _nbSlots;
}

Game::~Game() {}

std::string const&     Game::getName(void) {
    return _name;
}

bool     Game::canJoin(void) {
    return _nbSlots > _players.size();
}

void     Game::join(Player* player) {
   if (canJoin()) {
    _players.push_back(player);
   }
}

void     Game::quit(Player* player) {
    _players.erase(std::remove(_players.begin(), _players.end(), player), _players.end());
}

// TODO
void                Game::addGraphicElement(IGraphicElement* element) {
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) const {
	return new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);
}

ISprite*	Game::createSprite(ITexture *texture) const {
	return new Sprite(texture);
}

void		Game::loadMap(std::string const& fileName) {
	Map		map;

	if (map.load(fileName) == false)
		throw new Exception("Cannot load map: " + map.getError());
	std::list<Map::Object> const& objects = map.getObjects();
	for (std::list<Map::Object>::const_iterator it = objects.begin(); it != objects.end(); ++it) {
		try {
			GameObject	*obj = new GameObject(it->name);

			obj->init(this, it->params, it->xStart);
			_objects.push_back(obj);
		} catch (Exception *e) {
			throw e;
		} catch (...) {
			throw new Exception("Cannot load plugin: " + it->name);
		}
	}
}

void		Game::_sendGraphicElements(Network::UdpPacket &packet) {
	std::list<GraphicElement*>	toSend;

	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->hasChanged())
			toSend.push_back(*it);
	packet << toSend;
}
