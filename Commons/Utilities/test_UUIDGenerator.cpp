#include <iostream>
#include "Singleton.hpp"
#include "UUIDGenerator.h"

int main()
{
  UUIDGenerator a = Singleton<UUIDGenerator>::getInstance();

  std::cout << a.getUUID() << std::endl;
  std::cout << a.getUUID() << std::endl;
  std::cout << a.getUUID() << std::endl;

  UUIDGenerator b = Singleton<UUIDGenerator>::getInstance();

  std::cout << b.getUUID() << std::endl;
  std::cout << b.getUUID() << std::endl;
  std::cout << b.getUUID() << std::endl;

  return 0;
}
