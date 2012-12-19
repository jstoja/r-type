#ifndef _SFML_SOUND_H_
# define _SFML_SOUND_H_

# include <SFML/audio.hpp>
# include <iostream>
# include <string>
# include "Types.h"

namespace Sound {

  class	ISound;

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

    //! Id getter
    uint32	getId() const;

    //! Name getter
    std::string const&	getName() const;
  private:
    uint32			_id;
    std::string		_name;
    sf::SoundBuffer	_buf;
    sf::Sound		_sound;
  };

};

#endif
