//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Types.h"
#include "Widget.h"
#include "Graphic/FreetypeFont.h"
#include "Label.h"

Graphic::FreetypeFont   *Widget::Label::_font = NULL;

Widget::Label::Label(Graphic::Scene* scene,
                     Widget* parent) : Widget(scene, parent) {
    if (_font == NULL)
        _font = new Graphic::FreetypeFont(6);
}

Widget::Label::Label(Graphic::Scene* scene,
                     std::string const& text,
                     Widget* parent) : Widget(scene, parent), _text(text) {
    _element.setSize(Vec2(_text.size() - 1, 1.0));
    if (_font == NULL)
        _font = new Graphic::FreetypeFont(6);
}

Widget::Label::~Label() {
    delete _element.getSprite()->getTexture();
    delete _element.getSprite();
}

std::string const&  Widget::Label::getText() const {
    return _text;
}

void    Widget::Label::setText(std::string const& text) {
    _text = text;
    _element.setSize(Vec2(_text.size() - 1, 1.0));
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
        addElement();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

void    Widget::Label::update() {
    setSize(Vec2(_text.length(), 1));
    Graphic::Texture *texture = _font->getStringTexture(_text);
    delete _element.getSprite()->getTexture();
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
