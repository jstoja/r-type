//
// Block.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 14:06:26 2013 Samuel Olivier
//

#include <sstream>

#include "Block.h"

#include <IGame.h>
#include <IGraphicElement.h>

Block::Block() : _game(NULL), _block(NULL) {
}

void	Block::update() {
}

void	Block::init(IGame* game, ByteArray const& params, float32 xStart) {
	_game = game;
	_xStart = xStart;
	_graphicElement = game->createGraphicElement();
	std::stringstream	data(std::stringstream::in);
	data.write(params.getData(), params.getSize());
	game->addGraphicElement(_graphicElement);
}

float32	Block::getXStart() const {
	return _xStart;
}

RTYPE_PLUGIN_CREATE {
	return (new Block());
}
