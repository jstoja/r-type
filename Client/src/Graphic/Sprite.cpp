//
//  Sprite.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Sprite.h"

Graphic::Sprite::Frame::Frame(Vec2 const& p1, Vec2 const& p2)
: p1(p1), p2(p2) {
}

Graphic::Sprite::Sprite()
: Object(), _texture(NULL), _frames() {
}

Graphic::Sprite::Sprite(uint32 id)
: Object(id), _texture(NULL), _frames() {
}


Graphic::Sprite::~Sprite() {
}

Graphic::Texture* Graphic::Sprite::getTexture() const {
    return _texture;
}

void Graphic::Sprite::setTexture(Texture* texture) {
    _texture = texture;
}

void Graphic::Sprite::addFrame(Frame const& frame) {
    _frames.push_back(frame);
}

Graphic::Sprite::Frame const& Graphic::Sprite::getFrame(uint32 index) {
    return _frames[index];
}