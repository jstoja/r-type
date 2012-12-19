#ifndef _CHANNEL_GROUP_H_
# define _CHANNEL_GROUP_H_

# include <iostream>
# include <string>
# include <map>

namespace Sound {

  class Sound;
  class Channel;

  class ChannelGroup {
  public:
    //! Constructor
    ChannelGroup();

    //! Destructor
    ~ChannelGroup();

    //! Load sound into a channel
    bool	load(Sound*);

    //! Play sound by id
    void	play(uint32);

    //! Play sound by name
    void	play(std::string const&);

    //! Stop playing sound by name
    void	stop(std::string const&);

    //! Stop playing sound by id
    void	stop(uint32);

    //! Remove a sound by name
    void	remove(std::string const&);

    //! Remove a sound by id
    void	remove(uint32);

    //! isPlaying by id
    bool	isPlaying(uint32);

    //! isPlaying by name
    bool	isPlaying(std::string const&);

    //! Get sound by name
    Sound*	getSound(std::string const&);

    //! Get sound by id
    Sound*	getSound(uint32);
    
  private:
    std::vector<Channel*>	_channels;
  };

};

#endif
