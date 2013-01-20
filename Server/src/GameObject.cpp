//
// GameObject.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 15:01:02 2013 Samuel Olivier
//

#include <Library.h>
#include <LibraryFactory.h>
#include <Application.h>
#include <IPlugin.h>
#include <Exception.h>

#include "Server.h"
#include "GameObject.h"

GameObject::GameObject(std::string const& name) : _pluginName(name), _plugin(NULL) {
    _pluginMutex = new Threading::Mutex();
	_loadPlugin();
}


GameObject::~GameObject() {
    delete _pluginMutex;
	delete _plugin;
}

bool	GameObject::init(IGame* game, ByteArray const& params, float32 xStart) {
    Threading::MutexLocker locker(_pluginMutex);
	if (_plugin)
		return _plugin->init(game, params, xStart);
	return false;
}

void	GameObject::update(void *params) {
    Threading::MutexLocker locker(_pluginMutex);
	if (_plugin)
		_plugin->update();
}

float32	GameObject::getXStart() const {
    Threading::MutexLocker locker(_pluginMutex);
	if (_plugin)
		return (_plugin->getXStart());
	return (-1);
}

void	GameObject::_loadPlugin() {
	Library	*lib = LibraryFactory::getInstance().load(Application::getInstance().getRelativePath(Server::getPluginDirectory()), _pluginName);

    Threading::MutexLocker locker(_pluginMutex);
	if (lib == NULL)
		throw new Exception("Plugin " + _pluginName + " can't  be loaded");
	IPlugin::CreatorPrototype	creator = (IPlugin::CreatorPrototype)lib->resolve("newPlugin");
	if (creator == NULL)
		throw new Exception("The plugin " + _pluginName + " is not valid");
	_plugin = creator(_pluginName);
	if (_plugin == NULL)
		throw new Exception("The plugin " + _pluginName + " is not valid");
}
