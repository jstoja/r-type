//
// UUIDGenerator.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:16 2012 Samuel Olivier
//

#include "UUIDGenerator.h"

#ifndef OS_IOS
template <> UUIDGenerator* Singleton<UUIDGenerator>::_instance = new UUIDGenerator();
#endif

uint32 UUIDGenerator::_id = 0;

UUIDGenerator::UUIDGenerator() {
    _id = 0;
}

UUIDGenerator::~UUIDGenerator() {
}

uint32 UUIDGenerator::getUUID() {
    return _id++;
}
