#ifndef _UUIDGENERATOR_H_
# define __UUIDGENERATOR_H_

# include "Types.h"
# include "Singleton.hpp"

namespace Utilities {

  class UUIDGenerator : public Singleton<UUIDGenerator> {
    friend class Singleton<UUIDGenerator>;

  public:
    //! Construct the object
    UUIDGenerator();
    //! Destruct the object
    ~UUIDGenerator();

    //! Return and increment the UUID
    uint32 getUUID();

  private:
    static uint32 _id;
  };

}

#endif
