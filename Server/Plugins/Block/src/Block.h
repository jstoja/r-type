//
// Block.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 14:06:34 2013 Samuel Olivier
//


#ifndef _BLOCK_H_
# define _BLOCK_H_

# include <IPlugin.h>

class IGame;
class IGraphicElement;

class Block : public IPlugin {
public:
	Block(IGame* game);

	void	update();

private:
	IGame*				_game;
	IGraphicElement*	_graphicElement;
};

#endif