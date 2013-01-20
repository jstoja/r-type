//
// Bullet.h for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#include <sstream>
#include "Bullet.h"

Bullet::Bullet(std::string const& pluginName)
: _name(pluginName), _game(NULL), _graphicElement(NULL), _physicElement(NULL) {

}

Bullet::~Bullet() {
    
}

bool	Bullet::init(IGame* game, ByteArray const& params, float32 xStart) {
    if ((_game = game) == NULL) {
        return (false);
    }
    
    std::stringstream	data(std::stringstream::binary | std::stringstream::in | std::stringstream::out);
	data.write(params.getData(), params.getSize());
    
    Vec2 size;
    Vec3 from;
    Vec3 to;
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
    
    data.read(reinterpret_cast<char*>(&size), sizeof(size));
    data.read(reinterpret_cast<char*>(&from), sizeof(from));
    data.read(reinterpret_cast<char*>(&to), sizeof(to));
    data.read(reinterpret_cast<char*>(&_speed), sizeof(_speed));
    
    ISprite	*sprite = _game->getLevelSprite(name);
	if (sprite == NULL)
		return false;
	if ((_graphicElement = game->createGraphicElement()) == NULL)
		return false;
	if ((_physicElement = game->createPhysicElement()) == NULL)
		return false;
    
    _direction = to - from;
    
	_graphicElement->setPosition(from);
	_graphicElement->setSize(size);
	_graphicElement->setRotation(0);
	_graphicElement->setSprite(sprite);
	_graphicElement->setSpriteFrameIndex(frameIndex);
	_graphicElement->setType(IGraphicElement::Static);
	game->addGraphicElement(_graphicElement);
	_physicElement->setPosition(from);
	_physicElement->setSize(size);
	_physicElement->setRotation(0);
	_physicElement->setType(IPhysicElement::Static);
	game->addPhysicElement(_physicElement);
    
    return true;
}

void	Bullet::update() {
    Vec3 newPosition = _graphicElement->getPosition();
    
    newPosition.x += _direction.x*_speed*_game->getEllapsedTime()/1000;
    newPosition.y += _direction.y*_speed*_game->getEllapsedTime()/1000;
    
    _graphicElement->setPosition(newPosition);
    _physicElement->setPosition(newPosition);

    if (_game->getViewport()->isInViewport(_graphicElement->getRect())) {
        _xStart = -1;
    }
}

float32	Bullet::getXStart() const {
    return (_xStart);
}

std::string const&	Bullet::getName() const {
    return (_name);
}

RTYPE_PLUGIN_CREATE {
	return (new Bullet(name));
}