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
# include <Rect2.h>
# include <Types.h>

class IGraphicElement {
public:
	~IGraphicElement() {}

	virtual void	setPosition(Vec2 const& pos) = 0;
	virtual void	move(Vec2 const& pos) = 0;
	virtual void	setSize(Rect2 const& rect) = 0;
	virtual void	setRotation(float rotation) = 0;
};

#endif