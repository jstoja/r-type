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

ObjectManager::ObjectManager() {
}

ObjectManager::~ObjectManager() {
}
    
void	ObjectManager::addObject(Object *obj) {
	if (obj)
		_objects[obj->getId()] = obj;
}

void	ObjectManager::removeObject(Object *obj) {
	if (obj)
		_objects.erase(obj->getId());
}

Object*	ObjectManager::getObject(uint32 id) {
	return (_objects[id]);
}