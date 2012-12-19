#ifndef _SOUND_MANAGER_H_
# define _SOUND_MANAGER_H_

# include <iostream>
# include <string>
# include <map>
# include "Types.h"

namespace Sound {
  
  class	ISound;
  
  class	SoundManager {
  public:
    //! Constructor
    SoundManager();
    //! Destructor
    ~SoundManager();

    //! Load a sound
    void	load(std::string const&);
    //! Remove a sound by name
    void	remove(std::string const&);

    //! Play sound by name
    void	play(std::string const&);
    //! Play sound by id
    void	play(uint32);

    //! Get sound by id
    ISound	*getSound(uint32);
    //! Get sound by name
    ISound *getSound(std::string const&);

  private:
    std::map<uint32, ISound*>		_soundsId;
    std::map<std::string, ISound*>	_soundsName;
  };

}

#endif
