#include "UUIDGenerator.h"

int UUIDGenerator::_id = 0;

UUIDGenerator::UUIDGenerator() {
  _id = 0;
}

UUIDGenerator::~UUIDGenerator() {
}

int UUIDGenerator::getUUID() {
  return _id++;
}
