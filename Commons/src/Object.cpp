//
//  Object.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Object.h"
#include "ObjectManager.h"
#include "UUIDGenerator.h"

Object::Object(bool generateId) : _id(generateId ? UUIDGenerator::getInstance().getUUID() : (uint32)-1) {
	ObjectManager::getInstance().addObject(this);
}

Object::Object(uint32 id) : _id(id) {
	ObjectManager::getInstance().addObject(this);
}

Object::~Object() {
	ObjectManager::getInstance().removeObject(this);
}

uint32 Object::getId() const {
    return _id;
}

void Object::setId(uint32 id) {
    _id = id;
}

Object&	Object::operator=(Object const& obj) {
	return (*this);
}
