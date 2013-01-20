//
// ObjectManager.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 17:02:06 2013 Samuel Olivier
//

#include "ObjectManager.h"
#include "Object.h"

#ifndef OS_IOS
template <> ObjectManager* Singleton<ObjectManager>::_instance = new ObjectManager();
#endif

ObjectManager::ObjectManager() {
    _objects = new std::map<uint32, Object*>;
}

ObjectManager::~ObjectManager() {
	delete _objects;
}
    
void	ObjectManager::addObject(Object *obj) {
	if (obj)
		(*_objects)[obj->getId()] = obj;
}

void	ObjectManager::removeObject(Object *obj) {
	if (obj)
		_objects->erase(obj->getId());
}

Object*	ObjectManager::getObject(uint32 id) {
	return ((*_objects)[id]);
}