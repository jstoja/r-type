//
// IViewport.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 17 14:18:51 2013 Samuel Olivier
//

#ifndef _I_VIEWPORT_H_
# define _I_VIEWPORT_H_

# include <Types.h>
# include <Rect2.h>

class IViewport {
public:
	virtual ~IViewport() {}

	virtual void	setPosition(float32 x) = 0;
	virtual float32	getPosition() const = 0;

	virtual void	setWidth(float32 width) = 0;
	virtual float32	getWidth() const = 0;

	virtual void	setSpeed(float32 width) = 0;
	virtual float32	getSpeed() const = 0;

	virtual bool	isInViewport(Rect2 const& object) const = 0;
	virtual bool	isInViewport(float32 x) const = 0;
};

#endif