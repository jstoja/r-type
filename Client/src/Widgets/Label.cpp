//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Types.h"
#include "Widget.h"
#include "../Graphic/Image.h"
#include "../Graphic/Scene.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Element.h"
#include "GraphicWidget.h"
#include "Graphic/FreetypeFont.h"
#include "Label.h"

Graphic::FreetypeFont   *Widget::Label::_font = NULL;

Widget::Label::Label(Graphic::Scene* scene,
                     Widget* parent) : GraphicWidget(scene, parent) {
    if (_font == NULL)
        _font = new Graphic::FreetypeFont(6);
}

Widget::Label::Label(Graphic::Scene* scene,
                     std::string const& text,
                     Widget* parent) : GraphicWidget(scene, parent), _text(text) {
    setSize(Vec2(_text.size() - 1, 1.0));
    if (_font == NULL)
        _font = new Graphic::FreetypeFont(6);
}

Widget::Label::~Label() {
    delete getSprite()->getTexture();
    delete getSprite();
}

std::string const&  Widget::Label::getText() const {
    return _text;
}

void    Widget::Label::setText(std::string const& text) {
    _text = text;
    setSize(Vec2(_text.size() - 1, 1.0));
    update();
}

void    Widget::Label::init() {
    try {
        Graphic::Texture *texture = _font->getStringTexture(_text);

        Graphic::Sprite *sprite = new Graphic::Sprite();
        sprite->setTexture(texture);
        sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0,0.0), Vec2(1.0,1.0)));
        setSprite(sprite);
        setCurrentFrame(0);
        setSize(Vec2(_text.size() - 1, 1.0));
        addElement();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

void    Widget::Label::update() {
    setSize(Vec2(_text.length(), 1));
    Graphic::Texture *texture = _font->getStringTexture(_text);
    delete getSprite()->getTexture();
    Graphic::Sprite *sprite = getSprite();
    sprite->setTexture(texture);
}

void    Widget::Label::operator<<(char c) {
    setPosition(Vec2(getPosition().x + 0.5, getPosition().y));
    _text.push_back(c);
    update();
}

void    Widget::Label::operator<<(std::string const& str) {
    _text += str;
    update();
}

void    Widget::Label::clear() {
    setText(std::string(""));
}
