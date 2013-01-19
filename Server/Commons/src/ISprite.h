//
// ISprite.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 16:45:05 2013 Samuel Olivier
//

#ifndef _I_SPRITE_H_
# define _I_SPRITE_H_

# include <Rect2.h>
# include <ITexture.h>

class ISprite {
public:
	virtual ~ISprite() {}

	virtual void	setTexture(ITexture *texture) = 0;
	virtual ITexture*	getTexture() const = 0;
	virtual void	addFrame(Vec2 const& p1, Vec2 const& p2) = 0;
};

#endif