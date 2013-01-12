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

GameObject::GameObject(std::string const& name) : _plugin(NULL) {
	Library	*lib = LibraryFactory::getInstance().load(Application::getInstance().getRelativePath(Server::getPluginDirectory()), "Block");
	if (lib == NULL)
		throw new Exception("Plugin " + name + " can't  be loaded");
	IPlugin::CreatorPrototype	creator = (IPlugin::CreatorPrototype)lib->resolve("newPlugin");
	if (creator == NULL)
		throw new Exception("The plugin " + name + " is not valid");
	_plugin = creator();
	if (_plugin == NULL)
		throw new Exception("The plugin " + name + " is not valid");
}

GameObject::~GameObject() {
	delete _plugin;
}

void	GameObject::init(IGame* game, ByteArray const& params) {
	if (_plugin)
		_plugin->init(game, params);
}

void	GameObject::update() {
	if (_plugin)
		_plugin->update();
}
