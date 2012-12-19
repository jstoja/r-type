//
// UUIDGenerator.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:16 2012 Samuel Olivier
//

#include "UUIDGenerator.h"

uint32 Utilities::UUIDGenerator::_id = 0;

Utilities::UUIDGenerator::UUIDGenerator() {
  _id = 0;
}

Utilities::UUIDGenerator::~UUIDGenerator() {
}

uint32 Utilities::UUIDGenerator::getUUID() {
  return _id++;
}
