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
#include "Exception.h"
#include "Debug.h"

#ifndef OS_IOS
template <> ResourcesManager Singleton<ResourcesManager>::_instance = ResourcesManager();
#endif

ResourcesManager::ResourcesManager() {
    _resourcesId = new std::map<uint32, Resource*>;
    _resourcesName = new std::map<std::string, Resource*>;
}

ResourcesManager::~ResourcesManager() {
}

void ResourcesManager::removeResource(std::string const& name) {
    std::map<std::string, Resource*>::iterator it = _resourcesName->find(name);
    if (it != _resourcesName->end()) {
        _resourcesId->erase(it->second->getId());
        _resourcesName->erase(it->second->getName());
    }
}

Resource* ResourcesManager::loadResource(std::string const& name) {
    std::map<std::string, Resource*>::iterator it;

    if ((it = _resourcesName->find(name)) != _resourcesName->end())
      return it->second;
    Resource *res = new Resource(name);
    
    _resourcesName->at(name) = res;
    _resourcesId->at(res->getId()) = res;
    return res;
}

Resource*	ResourcesManager::getResource(std::string const& name) {
    std::map<std::string, Resource*>::const_iterator it;

    if ((it = _resourcesName->find(name)) != _resourcesName->end())
      return it->second;
    return loadResource(name);
}

Resource*	ResourcesManager::getResource(uint32 id) const {
    std::map<uint32, Resource*>::const_iterator it;

    if ((it = _resourcesId->find(id)) != _resourcesId->end())
        return it->second;
    throw new Exception("Cannot find resource with id " + id);
}
