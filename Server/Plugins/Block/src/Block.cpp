//
// Block.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 14:06:26 2013 Samuel Olivier
//

#include "Block.h"

#include <IGame.h>
#include <IGraphicElement.h>

Block::Block() : _game(NULL), _block(NULL) {
}

void	Block::update() {
	std::cout << "BOUYAKAAAA" << std::endl;
}

void	Block::init(IGame* game, ByteArray const& params) {
	_game = game;
}

RTYPE_PLUGIN_CREATE {
	return (new Block());
}