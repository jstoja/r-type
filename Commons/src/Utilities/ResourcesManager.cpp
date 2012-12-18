#include "Resource.h"
#include "ResourcesManager.h"

Utilities::ResourcesManager::ResourcesManager() {
}

Utilities::ResourcesManager::~ResourcesManager() {
}

void Utilities::ResourcesManager::addResource(Resource *resource) {
  _resources[resource->getName()] = resource;
}

void Utilities::ResourcesManager::removeResource(std::string const& name) {
  _resources.erase(name);
}
 
Utilities::Resource* Utilities::ResourcesManager::loadResource(std::string const& name) {
  Resource *res = new Resource(name);
  _resources[name] = res;
  return res;
}

Utilities::Resource*	Utilities::ResourcesManager::getResource(std::string const& name) {
  std::map<std::string, Resource*>::const_iterator it;

  if ((it = _resources.find(name)) != _resources.end())
    return it->second;
  return loadResource(name);
}
