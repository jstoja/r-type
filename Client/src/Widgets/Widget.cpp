//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include "Widget.h"

Widget::Widget::Widget(Widget* parent) {
    _parent = parent;
}

Widget::Widget::Widget(uint32 id) : Object(id) {
}

Widget::Widget::~Widget() {
}

void    Widget::Widget::setFocus(bool focus) {
    _focus = focus;
}

bool    Widget::Widget::hasFocus() const {
    return _focus;
}

void    Widget::Widget::setPosition(Vec2 const& v) {
    std::cerr << "lol" << std::endl;
    _element.setPosition(v);
    _position = v;
}

void    Widget::Widget::setSize(Vec2 const& v) {
    std::cerr << "lul" << std::endl;
    _element.setSize(v);
    _size = v;
}

Vec2 const&   Widget::Widget::getSize() const {
    return _size;
}

Vec2 const&   Widget::Widget::getPosition() const {
    return _position;
}

Graphic::Element *Widget::Widget::getElement() {
    return &_element;
}

bool    Widget::Widget::loadImage(const std::string &image_path) {
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