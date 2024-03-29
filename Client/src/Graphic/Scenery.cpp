//
//  Scenery.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Scenery.h"

Graphic::Scenery::Scenery(void) : Background(), _speed(1), _depth(0), _width(1) {
    
}

Graphic::Scenery::Scenery(uint32 id) : Background(id), _speed(1), _depth(0), _width(1) {
    
}

Graphic::Scenery::~Scenery(void) {
    
}

float32 Graphic::Scenery::getSpeed(void) const {
    return _speed;
}

void Graphic::Scenery::setSpeed(float32 speed) {
    _speed = speed;
}

float32 Graphic::Scenery::getDepth(void) const {
    return _depth;
}

void Graphic::Scenery::setDepth(float32 depth) {
    _depth = depth;
}

void Graphic::Scenery::setWidth(float32 width) {
    _width = width;
}

float32 Graphic::Scenery::getWidth(void) const {
    return _width;
}