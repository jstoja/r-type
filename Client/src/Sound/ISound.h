#ifndef _ISOUND_H_
# define _ISOUND_H_

# include <iostream>
# include <string>
# include "Types.h"

namespace Sound {

  class	ISound {
  public:
    virtual ~ISound() {}
    virtual void	play() = 0;
    virtual void	stop() = 0;
    virtual uint32 getId() const = 0;
    virtual std::string const& getName() const = 0;
  };

};

#endif
