//
// Sprite.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 17:27:36 2013 Samuel Olivier
//

#ifndef _SPRITE_H_
# define _SPRITE_H_

# include <list>

# include <ISprite.h>
# include <Object.h>
# include <Network/TcpPacket.h>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"
# include <Rect2.h>
# include "Frame.h"

class Texture;

class Sprite : public ISprite, public Object {
public:
	Sprite();
	Sprite(ITexture *texture);
	virtual ~Sprite();

	virtual void	setTexture(ITexture* texture);
 	virtual ITexture*	getTexture() const;
 	Texture*		_getTexture() const;

	virtual void			addFrame(Vec2 const& p1, Vec2 const& p2);
	std::list<Frame> const&	getFrames() const;

private:
    
    Threading::Mutex	*_attributesMutexTexture;
    Threading::Mutex	*_attributesMutexFrames;
	Texture*			_texture;
	std::list<Frame>	_frames;
};

Network::APacket&		operator<<(Network::APacket& packet, Sprite const& sprite);

#endif