#include "Resource.h"
#include "ResourcesManager.h"

int main()
{
  std::string marseille("marseille");
  Utilities::Resource	r;
  Utilities::Resource	r1("bite");
  Utilities::Resource	r2(marseille);
  Utilities::ResourcesManager rm;

  r = r1;
  std::cout<< r.getName() << std::endl;
  rm.addResource(&r);
  rm.addResource(&r2);
  
  Utilities::Resource *ret = rm.getResource(marseille);
  std::cout << ret->getName() << std::endl;
  ret = rm.getResource("bite");
  std::cout << ret->getName() << std::endl;
  rm.removeResource("bite");
  Utilities::Resource *lol = rm.getResource("bite");
  std::cout << lol->getName() << std::endl;
  return (0);
}
