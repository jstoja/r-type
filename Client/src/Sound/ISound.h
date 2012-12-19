#ifndef _ISOUND_H_
# define _ISOUND_H_

namespace Sound {

  class	ISound {
  public:
    virtual ~ISound() {}
    virtual void	play() = 0;
    virtual void	stop() = 0;
  };

};

#endif
