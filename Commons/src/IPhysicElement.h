//
// IPhysicElement.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:25:26 2013 Samuel Olivier
//

#ifndef _I_PHYSIC_ELEMENT_H_
# define _I_PHYSIC_ELEMENT_H_

# include <Vec2.h>
# include <Rect2.h>
# include <Types.h>

class IPhysicElement {
public:
	enum Type {
		Static = 0,
		Dynamic = 1,
		Floating = 2,
	};

	virtual ~IPhysicElement() {}

	virtual void	setPosition(Vec2 const& pos) = 0;
	virtual void	move(Vec2 const& pos) = 0;
	virtual Vec2 const& getPosition() const = 0;

	virtual void	setSize(Vec2 const& rect) = 0;
	virtual Vec2 const&	getSize() const = 0;

	virtual void	setRotation(float32 rotation) = 0;
	virtual float32	getRotation() const = 0;

	virtual void	setChanged(bool changed) = 0;
	virtual bool	hasChanged() const = 0;

	virtual void	setType(Type c) = 0;
	virtual Type	getType() const = 0;
};

#endif