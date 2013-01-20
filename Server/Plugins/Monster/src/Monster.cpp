//
// Monster.cpp for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#include <sstream>
#include "Monster.h"

Monster::Monster(std::string const& pluginName)
: _name(pluginName), _game(NULL) {
    
}

Monster::~Monster() {
}

bool	Monster::init(IGame* game, ByteArray const& params, float32 xStart) {
 	if ((_game = game) == NULL)
		return false;
    std::stringstream	data(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
	data.write(params.getData(), params.getSize());

    Vec3 pos;
    Vec2 size;
    float32 rotation;
    char *spriteName;
    uint32 spriteSize;
    char frameIndex;
    
    _xStart = xStart;
    
    data.read(reinterpret_cast<char*>(&spriteSize), sizeof(spriteSize));
    
    spriteName = new char[spriteSize];
	data.read(spriteName, spriteSize*sizeof(*spriteName));
	std::string name = std::string(spriteName, spriteSize);
	delete []spriteName;

    data.read(reinterpret_cast<char*>(&frameIndex), sizeof(frameIndex));
    
    ISprite	*sprite = _game->getLevelSprite(name);
	if (sprite == NULL)
		return false;
	if ((_graphicElement = game->createGraphicElement()) == NULL)
		return false;
	if ((_physicElement = game->createPhysicElement()) == NULL)
		return false;
    
    data.read(reinterpret_cast<char*>(&pos), sizeof(pos));
    data.read(reinterpret_cast<char*>(&size), sizeof(size));
    data.read(reinterpret_cast<char*>(&rotation), sizeof(rotation));

    
    data.read(reinterpret_cast<char*>(&_speed), sizeof(_speed));

	_graphicElement->setPosition(pos);
	_graphicElement->setSize(size);
	_graphicElement->setRotation(rotation);
	_graphicElement->setSprite(sprite);
	_graphicElement->setSpriteFrameIndex(frameIndex);
	_graphicElement->setType(IGraphicElement::Static);
	game->addGraphicElement(_graphicElement);
	_physicElement->setPosition(pos);
	_physicElement->setSize(size);
	_physicElement->setRotation(rotation);
	_physicElement->setType(IPhysicElement::Static);
	game->addPhysicElement(_physicElement);
	return true;
}

void	Monster::update() {
    Vec3 newPosition = _graphicElement->getPosition();
    
    newPosition.x += _speed * (float)_game->getEllapsedTime()/1000;
    
    _graphicElement->setPosition(newPosition);
    _physicElement->setPosition(newPosition);
    
	_xStart = (_game->getViewport()->isInViewport(_graphicElement->getRect())) ? -1 : (_game->getViewport()->getPosition() + _game->getViewport()->getWidth() / 2);
}

float32	Monster::getXStart() const {
    return (_xStart);
}

std::string const&	Monster::getName() const {
    return (_name);
}

RTYPE_PLUGIN_CREATE {
	return (new Monster(name));
}