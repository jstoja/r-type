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
#include <IPhysicElement.h>

Block::Block(std::string const& pluginName) : _game(NULL), _block(NULL), _name(pluginName) {
}

Block::~Block() {
}

void	Block::update() {
}

bool	Block::init(IGame* game, ByteArray const& params,
					float32 xStart) {
	if ((_game = game) == NULL)
		return false;
	_xStart = xStart;
	std::stringstream	data(std::stringstream::binary);
	data.write(params.getData(), params.getSize());
	Vec3	pos;
	Vec2	size;
	float32	rotation;
	uint32	nbr;
	char	*spriteName;
	char	idx;

	data >> pos.x >> pos.y >> pos.z >> size.x >> size.y >> rotation;
	spriteName = new char[nbr];
	data.read(spriteName, nbr);
	data >> idx;
	std::string name = std::string(spriteName, nbr);
	delete []spriteName;
	ISprite	*sprite = _game->getLevelSprite(name);
	if (sprite == NULL)
		return false;
	if ((_graphicElement = game->createGraphicElement()) == NULL)
		return false;
	if ((_physicElement = game->createPhysicElement()) == NULL)
		return false;
	_graphicElement->setPosition(pos);
	_graphicElement->setSize(size);
	_graphicElement->setRotation(rotation);
	_graphicElement->setSprite(sprite);
	_graphicElement->setSpriteFrameIndex(idx);
	_graphicElement->setType(IGraphicElement::Static);
	game->addGraphicElement(_graphicElement);
	_physicElement->setPosition(pos);
	_physicElement->setSize(size);
	_physicElement->setRotation(rotation);
	_physicElement->setType(IPhysicElement::Static);
	game->addPhysicElement(_physicElement);
	return true;
}

float32	Block::getXStart() const {
	return _xStart;
}

std::string const&	Block::getName() const {
	return (_name);
}

RTYPE_PLUGIN_CREATE {
	return (new Block(name));
}
