//
//  Object.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Object.h"

#include "UUIDGenerator.h"

Object::Object() : _id(0) {
    _id = UUIDGenerator::getInstance().getUUID();
}

Object::Object(uint32 id) : _id(id) {
}

Object::~Object() {
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
