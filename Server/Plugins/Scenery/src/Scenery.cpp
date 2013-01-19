//
// Scenery.cpp for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#include <sstream>

#include "Scenery.h"
#include "ISprite.h"

Scenery::Scenery(std::string const& pluginName)
    : _game(NULL), _name(pluginName), _scenery(NULL) {
    
}

Scenery::~Scenery() {
}

bool                Scenery::init(IGame* game, ByteArray const& params, float32 xStart) {
 	if ((_game = game) == NULL)
		return false;
    _scenery = _game->addScenery();
    
    if (_scenery == NULL) {
        return false;
    }
    
    uint32 spriteSize;
    char *spriteName;
    float32 speed;
    float32 width;
    float32 xEnd;
    float32 depth;
    float32 opacity;
    
    std::stringstream	data(std::stringstream::binary);
	data.write(params.getData(), params.getSize());
    
    data.read(reinterpret_cast<char*>(&spriteSize), sizeof(spriteSize));
    
    spriteName = new char[spriteSize];
	data.read(spriteName, spriteSize*sizeof(*spriteName));
	std::string spriteVal(spriteName, spriteSize);
	delete []spriteName;
	ISprite*	sprite = _game->getLevelSprite(spriteVal);
	if (sprite == NULL)
		return (false);
	ITexture*	texture = sprite->getTexture();
    if (texture == NULL)
        return false;
    data.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    data.read(reinterpret_cast<char*>(&width), sizeof(width));
    data.read(reinterpret_cast<char*>(&xEnd), sizeof(xEnd));
    data.read(reinterpret_cast<char*>(&depth), sizeof(depth));
    data.read(reinterpret_cast<char*>(&opacity), sizeof(opacity));
    _scenery->setTexture(texture);
    _scenery->setWidth(width);
    _scenery->setXStart(xStart);
    _scenery->setXEnd(xEnd);
    _scenery->setSpeed(speed);
    _scenery->setDepth(depth);
    _scenery->setOpacity(opacity);
    return (true);
}

void                Scenery::update() {
}

float32             Scenery::getXStart() const {
    return (-1);
}

std::string const&	Scenery::getName() const {
    return (_name);
}