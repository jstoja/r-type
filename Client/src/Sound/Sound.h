//
//  Sound.h
//  r-type
//
//  Created by Franck Lavisse on 19/12/12.
//
//
#ifndef _SFML_SOUND_H_
# define _SFML_SOUND_H_

# include <iostream>
# include <string>
# include "Types.h"
# include "OS.h"

# if (defined OS_IOS)
#  define AUDIO_IOS
# else
#  define AUDIO_SFML
# endif

# ifdef AUDIO_SFML
# include <SFML/Audio.hpp>
# endif

class ByteArray;
class Resource;

namespace Sound {
	class	Sound {
		public:
			//! Constructor
            Sound(Resource *);

			//! Destructor
			~Sound(void);

			//! Load a sound
			void				load(Resource *);

			//! Play sound
			void				play();

			//! Stop playing sound
			void				stop();

			//! Id getter
			uint32				getId() const;

			//! Name getter
			std::string const&	getName() const;

			//! Return true if son is playing
			bool				isPlaying() const;

			//! Comparaison operator
			bool				operator==(Sound const&);

		private:
			uint32				_id;
			std::string			_name;
# ifdef AUDIO_SFML
			sf::SoundBuffer		_buf;
			sf::Sound			_sound;
# endif
    };
};

#endif
