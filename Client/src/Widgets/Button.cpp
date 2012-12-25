//
//  Button.cpp
//  R-Type
//
//  Created by Julien Bordellier on 25/12/12.
//
//

#include <SFML/Graphics.hpp>
#include "Button.h"

Widget::Button::Button(void) :
Object(), _element(NULL) {
    
}

Widget::Button::Button(uint32 id) :
Object(id), _element(NULL) {
}

Widget::Button::~Button() {
}

bool    Widget::Button::loadImage(const std::string &image_path) {
    sf::Image image;
    image.loadFromFile(image_path.c_str());
    
    Graphic::Texture* buttonTexture = new Graphic::Texture();
    buttonTexture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    Graphic::Sprite* buttonSprite = new Graphic::Sprite();
    buttonSprite->setTexture(buttonTexture);

    // THIS SECTION HAS TO MOVE OUT AFTER
    buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0,  1.0)));
    _element.setSprite(buttonSprite);
    _element.setCurrentFrame(0);
    //
    
    return true;
}

uint32  Widget::Button::setAutoFrames(uint32 framesNumber, framesOrientation orientation) {
    return 0;
}

uint32  Widget::Button::setManualFrame(const Graphic::Sprite::Frame &frame) {
    return 0;
}

void Widget::Button::setPosition(const Vec2 &position) {
    _position = position;
}

void Widget::Button::setSize(const Vec2 &size) {
    _size = size;
}

Vec2 const &Widget::Button::getPosition(void) const {
    return _position;
}

Vec2 const &Widget::Button::getSize(void) const {
    return _size;
}

Graphic::Element *Widget::Button::getElement() {
    return &_element;
}