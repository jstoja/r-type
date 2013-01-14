//
// Sound.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 01:09:40 2013 Samuel Olivier
//

#ifndef _SOUND_H_
# define _SOUND_H_

# include <string>

# include <ISound.h>
# include <Object.h>
# include <Resource.h>
# include <Network/TcpPacket.h>

class Sound : public ISound, public Object {
public:
	Sound(std::string const& filepath);
	virtual ~Sound();

	Resource*	getSound() const;

	virtual void	setRepeat(int32 repeat);
	virtual int32	getRepeat() const;

	virtual void	play();
	virtual void	stop();

	virtual bool	hasChanged() const;
	virtual void	setChanged(bool val);

private:
	Resource*	_sound;
	bool		_changed;
	bool		_isPlaying;
	int32		_repeat;
};

Network::APacket&		operator<<(Network::APacket& packet, Sound const& texture);

#endif