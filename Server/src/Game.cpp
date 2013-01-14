//
// Game.cpp by Melvin Laplanche
// 01-11-13
//

#include <algorithm>

#include <Application.h>
#include <Exception.h>
#include <Resource.h>

#include "Game.h"
#include "GraphicElement.h"
#include "Texture.h"
#include "Sprite.h"
#include "GameObject.h"

Game::Game(Network::TcpPacket* packet) : _updatePool(new Threading::ThreadPool(_updateThreadNumber)) {
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

void                Game::addGraphicElement(IGraphicElement* element) {
	_graphicScene.addElement(dynamic_cast<GraphicElement*>(element));
}

IGraphicElement*    Game::createGraphicElement() const {
	return (new GraphicElement());
}

ITexture*	Game::createTexture(std::string const& filename, std::string const& pluginName) {
	Texture *res = new Texture("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + filename);
	_gameTextures.push_back(res);
	return res;
}

ISprite*	Game::createSprite(ITexture *texture) {
	Sprite	*res = new Sprite(texture);
	_gameSprites.push_back(res);
	return res;
}

ISprite*	Game::getLevelSprite(std::string const& name) {
	return (_levelSprites[name]);	
}

void		Game::addPhysicElement(IPhysicElement* element) {
	_physicScene.addElement(dynamic_cast<PhysicElement*>(element));
}

IPhysicElement*	Game::createPhysicElement() const {
	return (new PhysicElement());
}

ISound*			Game::loadSound(std::string const& name, std::string const& pluginName) {
	Sound *res= new Sound("Plugins" + Application::getInstance().getDirectorySeparator() +
			pluginName + Application::getInstance().getDirectorySeparator() + name);
	_gameSounds.push_back(res);
	return res;
}

ISound*			Game::loadSound(std::string const& name) {
	Sound *res= new Sound("Levels" + Application::getInstance().getDirectorySeparator() +
		_currentLevel.getFilename() + Application::getInstance().getDirectorySeparator() + name);
	_gameSounds.push_back(res);
	return res;
}

IScenery*		Game::addScenery() {
	Scenery	*res = new Scenery();
	_gameSceneries.push_back(res);
	return (res);
}

void		Game::loadMap(std::string const& fileName) {
	if (_currentLevel.load(fileName) == false)
		throw new Exception("Cannot load map: " + _currentLevel.getError());
	std::list<Map::Object> const& objects = _currentLevel.getObjects();
	std::map<std::string, Texture*> const&	textures = _currentLevel.getTextures();
	_levelSprites = _currentLevel.getSprites();
	for (std::map<std::string, Texture*>::const_iterator it = textures.begin(); it != textures.end(); ++it)
		_gameTextures.push_back(it->second);
	for (std::map<std::string, Sprite*>::const_iterator it = _levelSprites.begin(); it != _levelSprites.end(); ++it)
		_gameSprites.push_back(it->second);
	for (std::list<Map::Object>::const_iterator it = objects.begin(); it != objects.end(); ++it) {
		try {
			GameObject	*obj = new GameObject(it->name);

			if (obj->init(this, it->params, it->xStart) == false)
				throw new Exception("Cannot init plugin: " + it->name);
			_objects.push_back(obj);
		} catch (Exception *e) {
			throw e;
		} catch (...) {
			throw new Exception("Cannot load plugin: " + it->name);
		}
	}
}

void	Game::_sendResources(Network::TcpPacket &packet) {
	std::list<Resource*>	resources;
	for (std::list<Texture*>::iterator it = _gameTextures.begin(); it != _gameTextures.end(); ++it)
		resources.push_back((*it)->getImg());
	for (std::list<Sound*>::iterator it = _gameSounds.begin(); it != _gameSounds.end(); ++it)
		resources.push_back((*it)->getSound());
	packet << resources << _gameTextures << _gameSprites;
	_graphicScene.sendStaticElements(packet);
	_physicScene.sendStaticElements(packet);
	packet << _gameSceneries << _gameSounds;
}

void	Game::_update() {
	for (std::list<GameObject*>::iterator it = _objects.begin();
		it != _objects.end(); ++it)
		_updatePool->addTask(*it, &GameObject::update, NULL);
}
