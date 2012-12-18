#ifndef _UUIDGENERATOR_H_
# define __UUIDGENERATOR_H_

# include "../Singleton.hpp"

namespace Utilities {

  class UUIDGenerator : public Singleton<UUIDGenerator> {
    friend class Singleton<UUIDGenerator>;

  public:
    UUIDGenerator();
    ~UUIDGenerator();

    int getUUID();

  private:
    static int _id;
  };

}

#endif
