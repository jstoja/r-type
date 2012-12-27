//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include "Widget.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Sprite.h"
#include "Label.h"

Widget::Label::Label() : Widget() {
}

Widget::Label::Label(std::string const& text) : Widget(), _text(text) {
}

Widget::Label::~Label() {
}

std::string const&  Widget::Label::getText() const {
    return _text;
}

void    Widget::Label::setText(std::string const& text) {
    _text = text;
}

void    Widget::Label::init() {
    try {
        sf::Image   image;
        image.loadFromFile("alphabet.png");
        Graphic::Texture*   labelTexture = new Graphic::Texture();
        labelTexture->setData(image.getSize().x,
                              image.getSize().y,
                              image.getPixelsPtr());
        Graphic::Sprite*    labelSprite = new Graphic::Sprite();
        labelSprite->setTexture(labelTexture);
        labelSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.03, 0.08),
                                                     Vec2(0.15, 0.22)));
        _element.setSprite(labelSprite);
        _element.setCurrentFrame(0);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    
}

void    Widget::Label::setFrame() {
    //Graphic::Sprite*    sp = _element.getSprite();
    //Graphic::Sprite::Frame f(Vec2(0,0), Vec2(1,1));
    //sp->addFrame(f);
    //_element.setCurrentFrame(0);
}