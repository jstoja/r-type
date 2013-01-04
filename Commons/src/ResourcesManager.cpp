//
// ResourcesManager.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:32 2012 Samuel Olivier
//

#include "Resource.h"
#include "ResourcesManager.h"

ResourcesManager::ResourcesManager() {
}

ResourcesManager::~ResourcesManager() {
	for (std::map<std::string, Resource*>::iterator it = _resourcesName.begin();
		it != _resourcesName.end(); ++it) {
		delete it->second;
	}
}

void ResourcesManager::removeResource(std::string const& name) {
    Resource *item = getResource(name);
    if (item != NULL) {
        _resourcesId.erase(item->getId());
        _resourcesName.erase(item->getName());
		delete item;
    }
}

Resource* ResourcesManager::loadResource(std::string const& name) {
    std::map<std::string, Resource*>::iterator it;

    if ((it = _resourcesName.find(name)) != _resourcesName.end())
      return it->second;
    Resource *res = new Resource(name);
    
    _resourcesName[name] = res;
    _resourcesId[res->getId()] = res;
    return res;
}

Resource*	ResourcesManager::getResource(std::string const& name) {
    std::map<std::string, Resource*>::const_iterator it;

    if ((it = _resourcesName.find(name)) != _resourcesName.end())
      return it->second;
    return NULL;
}

Resource*	ResourcesManager::getResource(uint32 id) const {
    std::map<uint32, Resource*>::const_iterator it;

    if ((it = _resourcesId.find(id)) != _resourcesId.end())
        return it->second;
    return NULL;
}
