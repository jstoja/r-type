#include "UUIDGenerator.h"

int UUIDGenerator::_id = 0;

Utilities::UUIDGenerator::UUIDGenerator() {
  _id = 0;
}

Utilities::UUIDGenerator::~UUIDGenerator() {
}

int Utilities::UUIDGenerator::getUUID() {
  return _id++;
}
