#include "Resource.h"
#include "ResourcesManager.h"

Utilities::ResourcesManager::ResourcesManager() {
}

Utilities::ResourcesManager::~ResourcesManager() {
}

void Utilities::ResourcesManager::addResource(Resource *resource) {
  _resourcesName[resource->getName()] = resource;
  _resourcesId[resource->getId()] = resource;
}

void Utilities::ResourcesManager::removeResource(std::string const& name) {
  Resource *item = getResource(name);
  if (item != NULL) {
      _resourcesId.erase(item->getId());
      _resourcesName.erase(item->getName());
    }
}
 
Utilities::Resource* Utilities::ResourcesManager::loadResource(std::string const& name) {
  Resource *res = new Resource(name);
  _resourcesName[name] = res;
  _resourcesId[res->getId()] = res;
  return res;
}

Utilities::Resource*	Utilities::ResourcesManager::getResource(std::string const& name) {
  std::map<std::string, Resource*>::const_iterator it;

  if ((it = _resourcesName.find(name)) != _resourcesName.end())
    return it->second;
  return NULL;
}

Utilities::Resource*	Utilities::ResourcesManager::getResource(uint32 id) const {
  std::map<uint32, Resource*>::const_iterator it;  

  if ((it = _resourcesId.find(id)) != _resourcesId.end())
    return it->second;
  return NULL;
}
