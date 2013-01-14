//
// IGraphicElement.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 17:07:28 2013 Samuel Olivier
//

#ifndef _I_GRAPHIC_ELEMENT_H_
# define _I_GRAPHIC_ELEMENT_H_

# include <Vec2.h>
# include <Vec3.h>
# include <Rect2.h>
# include <Types.h>

class ISprite;

class IGraphicElement {
public:
	enum Type {
		Static = 0,
		Dynamic = 1,
		Floating = 2,
	};

	virtual ~IGraphicElement() {}

	virtual void	setPosition(Vec3 const& pos) = 0;
	virtual void	move(Vec3 const& pos) = 0;
	virtual Vec3 const& getPosition() const = 0;

	virtual void	setSize(Vec2 const& rect) = 0;
	virtual Vec2 const&	getSize() const = 0;

	virtual void	setRotation(float32 rotation) = 0;
	virtual float32	getRotation() const = 0;

	virtual void	setChanged(bool changed) = 0;
	virtual bool	hasChanged() const = 0;

	virtual void	setSprite(ISprite *sprite) = 0;

	virtual void	setSpriteFrameIndex(char idx) = 0;
	virtual char	getSpriteFrameIndex() const = 0;

	virtual void	setType(Type c) = 0;
	virtual Type	getType() const = 0;
};

#endif