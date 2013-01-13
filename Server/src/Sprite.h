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
# include <Rect2.h>

class Texture;

class Sprite : public ISprite, public Object {
public:
	Sprite();
	Sprite(ITexture *texture);
	virtual ~Sprite();

	virtual void	setTexture(ITexture* texture);
	Texture*		getTexture() const;

	virtual void				addFrame(Rect2 const& frame);
	std::list<Rect2> const&	getFrames() const;

private:
	Texture*			_texture;
	std::list<Rect2>	_frames;
};

Network::TcpPacket&		operator<<(Network::TcpPacket& packet, Sprite const& sprite);

#endif