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
