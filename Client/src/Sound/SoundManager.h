//
//  SoundManager.h
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//
#ifndef _SOUND_MANAGER_H_
# define _SOUND_MANAGER_H_

# include <iostream>
# include <string>
# include <map>
# include <list>
# include "Types.h"

namespace Sound {
  
  class	Sound;
  class	ChannelGroup;

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
    //! Remove a sound by id
    void	remove(uint32);

    //! Play sound by name
    void	play(std::string const&);
    //! Play sound by id
    void	play(uint32);

    //! Get sound by id
    Sound	*getSound(uint32);
    //! Get sound by name
    Sound *getSound(std::string const&);

    //! isPlaying by id
    bool	isPlaying(uint32);

    //! isPlaying by name
    bool	isPlaying(std::string const&);
  private: 
    std::list<ChannelGroup*>			_channelsGroups;
    std::map<uint32, Sound*>			_soundsId;
    std::map<std::string, Sound*>		_soundsName;
  };

}

#endif
