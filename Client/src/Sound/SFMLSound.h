#ifndef _SFML_SOUND_H_
# define _SFML_SOUND_H_

# include <SFML/audio.hpp>
# include <iostream>
# include <string>
# include "ISound.h"

namespace Sound {

  class	SFMLSound : public ISound {
  public:
    //! Constructor
    SFMLSound(std::string const&);
    //! Destructor
    ~SFMLSound();
    //! Load a sound
    void	load(std::string const&);
    //! Play sound
    void	play();
    //! Stop playing sound
    void	stop();
  private:
    int			_id;
    std::string		_name;
    sf::SoundBuffer	_buf;
    sf::Sound		_sound;
  };

};

#endif
