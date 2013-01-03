//
//  Button.cpp
//  R-Type
//
//  Created by Julien Bordellier on 25/12/12.
//
//
#include "../Graphic/Sprite.h"
#include "Button.h"

Widget::Button::Button(Widget* parent) :
    Widget(parent) {
    
}

Widget::Button::Button(Vec2 const& size,
                       Vec2 const& position,
                       std::string const& image,
                       Widget* parent) :
    Widget(parent) {
    setPosition(position);
    setSize(size);
    loadImage(image);
}

Widget::Button::~Button() {
}

uint32  Widget::Button::setAutoFrames(uint32 framesNumber, framesOrientation orientation) {
    return 0;
}

uint32  Widget::Button::setManualFrame(const Graphic::Sprite::Frame &frame) {
    _element.getSprite()->addFrame(frame);
    return 0;
}

void    Widget::Button::setCurrentFrame(uint32 nb) {
    _element.setCurrentFrame(nb);
}