//
//  Scenery.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Scenery.h"

Graphic::Scenery::Scenery(void) : Background(), _speed(1), _depth(0) {
    
}

Graphic::Scenery::Scenery(uint32 id) : Background(id), _speed(1), _depth(0) {
    
}

Graphic::Scenery::~Scenery(void) {
    
}

float32 Graphic::Scenery::getSpeed(void) const {
    return _speed;
}

void Graphic::Scenery::setSpeed(float32 speed) {
    _speed = speed;
}