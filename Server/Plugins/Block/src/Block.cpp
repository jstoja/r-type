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

Block::Block(IGame *game) : _game(game) {
	IGraphicElement	*elem = game->createGraphicElement();
}

void	Block::update() {

}

extern "C" PLUGIN_EXPORT IPlugin	*newPlugin(IGame *game) {
	return (new Block(game));
}