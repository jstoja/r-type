//
// UUIDGenerator.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:29 2012 Samuel Olivier
//

#ifndef _UUIDGENERATOR_H_
# define _UUIDGENERATOR_H_

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
