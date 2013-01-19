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

Block::Block(std::string const& pluginName)
    : _game(NULL), _graphicElement(NULL), _physicElement(NULL), _name(pluginName) {
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
	std::stringstream	data(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
	data.write(params.getData(), params.getSize());

	Vec3	pos;
	Vec2	size;
	float32	rotation;
	uint32	spriteSize;
	char	*spriteName;
	char	idx;
    
    data.read(reinterpret_cast<char*>(&pos), sizeof(pos));
    data.read(reinterpret_cast<char*>(&size), sizeof(size));
    data.read(reinterpret_cast<char*>(&rotation), sizeof(rotation));
    data.read(reinterpret_cast<char*>(&spriteSize), sizeof(spriteSize));

	spriteName = new char[spriteSize];
	data.read(spriteName, spriteSize*sizeof(*spriteName));
	std::string name = std::string(spriteName, spriteSize);
	delete []spriteName;
    
	data.read(&idx, sizeof(idx));
    
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
