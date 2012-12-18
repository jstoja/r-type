#ifndef _UUIDGENERATOR_H_
# define __UUIDGENERATOR_H_

#include "Singleton.hpp"

class UUIDGenerator {
 public:
  UUIDGenerator();
  ~UUIDGenerator();
  int getUUID();
 private:
  static int _id;
};

#endif
