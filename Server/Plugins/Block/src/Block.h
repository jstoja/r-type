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
	Block();

	virtual void	init(IGame* game, ByteArray const& params, float32 xStart);
	virtual void	update();
	virtual float32	getXStart() const;

private:
	IGame*				_game;
	IGraphicElement*	_block;
	float32				_xStart;
	IGraphicElement*	_graphicElement;
};

#endif