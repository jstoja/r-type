#include "UUIDGenerator.h"

uint32_t Utilities::UUIDGenerator::_id = 0;

Utilities::UUIDGenerator::UUIDGenerator() {
  _id = 0;
}

Utilities::UUIDGenerator::~UUIDGenerator() {
}

uint32_t Utilities::UUIDGenerator::getUUID() {
  return _id++;
}
