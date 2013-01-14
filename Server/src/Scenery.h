//
// Scenery.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 14:43:15 2013 Samuel Olivier
//

#ifndef _SCENERY_H_
# define _SCENERY_H_

# include <string>

# include <IScenery.h>
# include <Object.h>
# include <Network/TcpPacket.h>

# include "Texture.h"

class Scenery : public IScenery, public Object {
public:
	Scenery();
	virtual ~Scenery();

	virtual void		setTexture(ITexture* texture);
	virtual Texture*	getTexture() const;
	
	virtual void	setSpeed(float32 speed);
	virtual float32	getSpeed() const;

	virtual void	setWidth(float32 width);
	virtual float32	getWidth() const;

	virtual void	setXStart(float32 xStart);
	virtual float32	getXStart() const;

	virtual void	setXEnd(float32 xEnd);
	virtual float32	getXEnd() const;

private:
	Texture*	_texture;
	float32		_speed;
	float32		_width;
	float32		_xStart;
	float32		_xEnd;
};

Network::APacket&		operator<<(Network::APacket& packet, Scenery const& texture);

#endif