//
//  Background.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Background.h"

Graphic::Background::Background(void)
: Object(), _texture(NULL), _range(), _repeat(1) {
}

Graphic::Background::Background(uint32 id)
: Object(id), _texture(NULL), _range(), _repeat(1) {
}

Graphic::Background::~Background() {
}

void Graphic::Background::setTexture(Texture* texture) {
    _texture = texture;
}

Graphic::Texture* Graphic::Background::getTexture(void) const {
    return _texture;
}

Vec2 const& Graphic::Background::getRange(void) const {
    return _range;
}

void Graphic::Background::setRange(Vec2 const& range) {
    _range = range;
}

float32 Graphic::Background::getRepeat(void) const {
    return _repeat;
}

void Graphic::Background::setRepeat(float32 repeat) {
    _repeat = repeat;
}
