#ifndef _SFML_SOUND_H_
# define _SFML_SOUND_H_

# include <SFML/audio.hpp>
# include <iostream>
# include <string>
# include "Types.h"

namespace Sound {

  class	Sound {
  public:
    //! Constructor
    Sound(std::string const&);

    //! Destructor
    ~Sound();

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

    //! Return true if son is playing
    bool	isPlaying() const;

    //! Comparaison operator
    bool	operator==(Sound const&);

  private:
    uint32			_id;
    std::string		_name;
    sf::SoundBuffer	_buf;
    sf::Sound		_sound;
  };

};

#endif
