#ifndef _CHANNEL_H_
# define _CHANNEL_H_

# include <iostream>
# include <string>
# include "Types.h"

namespace Sound {

  class Sound;

  class Channel {
  public:
    //! Constructor with sound
    Channel(Sound*);

    //! Destructor
    ~Channel();

    //! Set sound
    void	setSound(Sound*);

    //! Play sound
    void	play();

    //! Stop playing sound
    void	stop();

    //! return true if sound is playing
    bool	isPlaying() const;

    //! Get sound id
    uint32	getId() const;

    //! Get sound name
    std::string const&	getName() const;

    //! Get sound
    Sound*	getSound() const;
  private:
    Sound*	_sound;
  };

};

#endif
