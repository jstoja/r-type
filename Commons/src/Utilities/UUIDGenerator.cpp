#include "UUIDGenerator.h"

int Utilities::UUIDGenerator::_id = 0;

Utilities::UUIDGenerator::UUIDGenerator() {
  _id = 0;
}

Utilities::UUIDGenerator::~UUIDGenerator() {
}

int Utilities::UUIDGenerator::getUUID() {
  return _id++;
}
