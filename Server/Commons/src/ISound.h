//
// ISound.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 01:05:17 2013 Samuel Olivier
//

#ifndef _I_SOUND_H_
# define _I_SOUND_H_

# include <Types.h>

class ISound {
public:
	virtual ~ISound() {}

	virtual void	setRepeat(int32 repeat) = 0;
	virtual int32	getRepeat() const = 0;

	virtual void	play() = 0;
	virtual void	stop() = 0;

	virtual bool	hasChanged() const = 0;
	virtual void	setChanged(bool val) = 0;
};

#endif