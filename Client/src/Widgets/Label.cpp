//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Label.h"

# ifdef OS_IOS

void Widget::Label::_init(void) {
}

void    Widget::Label::update() {
}

# else

Graphic::FreetypeFont *Widget::Label::_font = NULL;

void Widget::Label::_init(void) {
    if (_font == NULL)
        _font = new Graphic::FreetypeFont(6);
}

void Widget::Label::update() {
    setSize(Vec2(_text.length(), 1));
    Graphic::Texture *texture = _font->getStringTexture(_text);
    delete getSprite()->getTexture();
    Graphic::Sprite *sprite = getSprite();
    sprite->setTexture(texture);
}


# endif

Widget::Label::Label(Graphic::Scene* scene,
                     Widget* parent) : GraphicWidget(scene, parent) {
    _init();
}

Widget::Label::Label(Graphic::Scene* scene,
                     std::string const& text,
                     Widget* parent) : GraphicWidget(scene, parent), _text(text) {
    setSize(Vec2(_text.size() - 1, 1.0));
    _init();
}

Widget::Label::~Label() {
    if (getSprite())
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

void    Widget::Label::operator<<(char c) {
    setPosition(Vec3(getPosition().x + 0.5, getPosition().y));
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
