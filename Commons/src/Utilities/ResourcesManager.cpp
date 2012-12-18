#include "ResourcesManager.h"

Utilities::ResourcesManager::ResourcesManager() {
}

Utilities::ResourcesManager::~ResourcesManager() {
}

void Utilities::ResourcesManager::addResource(std::string const& name, Resource *resource) {
  (void)name;
  (void)resource;
}

void Utilities::ResourcesManager::removeResource(std::string const& name) {
  (void)name;
}
 
Utilities::Resource*	Utilities::ResourcesManager::getResource(std::string const& name) {
  (void)name;
  return NULL;
}
