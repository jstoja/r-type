//
// IGame.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 10:40:05 2013 Samuel Olivier
//

#ifndef _I_GAME_H_
# define _I_GAME_H_

class IGraphicElement;

class IGame {
public:
	~IGame() {}
	virtual void	addGraphicElement(IGraphicElement* element) = 0;

	virtual IGraphicElement*	createGraphicElement() = 0;
};

#endif