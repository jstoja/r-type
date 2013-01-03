//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "Types.h"
#include "Widget.h"
#include "../Graphic/Texture.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Font.h"
#include "Label.h"

Graphic::FreetypeFont   *Widget::Label::_font = NULL;

Widget::Label::Label(Widget* parent) : Widget(parent) {
    if (_font == NULL) {
        _font = new Graphic::FreetypeFont();
        _font->init("/Library/Fonts/Marion.ttc", 9);
	}
}

Widget::Label::Label(std::string const& text, Widget* parent) : Widget(parent), _text(text) {
    if (_font == NULL)
        _font = new Graphic::FreetypeFont();
        _font->init("/Library/Fonts/Marion.ttc", 9);
}

Widget::Label::~Label() {
}

std::string const&  Widget::Label::getText() const {
    return _text;
}

void    Widget::Label::setText(std::string const& text) {
    _text = text;
    update();
}

void    Widget::Label::init() {
    try {
        Graphic::Texture *texture = _font->getStringTexture(_text);

        Graphic::Sprite *sprite = new Graphic::Sprite();
        sprite->setTexture(texture);
        sprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0,0.0), Vec2(1.0,1.0)));
        _element.setSprite(sprite);
        _element.setCurrentFrame(0);
        _element.setSize(Vec2(_text.size() - 1, 1.0));
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

void    Widget::Label::update() {
    setSize(Vec2(_text.length(), 1));
    Graphic::Texture *texture = new Graphic::Texture();
    texture->setData(_font->getStringWidth(_text),
                     _font->getStringHeight(_text),
                     _font->stringData(_text));
    Graphic::Sprite *sprite = _element.getSprite();
    sprite->setTexture(texture);
}

void    Widget::Label::operator<<(char c) {
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
