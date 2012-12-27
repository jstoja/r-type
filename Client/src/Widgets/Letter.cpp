//
//  Letter.cpp
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#include <SFML/Graphics.hpp>
#include "../Graphic/Texture.h"
#include "../Graphic/Sprite.h"
#include "Widget.h"
#include "Letter.h"

Widget::Letter::Letter() : Widget() {
    
}

Widget::Letter::~Letter() {
    
}

void    Widget::Letter::loadLetter(sf::Image const& img) {
    Graphic::Texture*   labelTexture = new Graphic::Texture();
    labelTexture->setData(img.getSize().x,
                          img.getSize().y,
                          img.getPixelsPtr());
    Graphic::Sprite*    labelSprite = new Graphic::Sprite();
    labelSprite->setTexture(labelTexture);
    labelSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.03, 0.08),
                                                 Vec2(0.15, 0.22)));
    _element.setSprite(labelSprite);
    _element.setCurrentFrame(0);
}

