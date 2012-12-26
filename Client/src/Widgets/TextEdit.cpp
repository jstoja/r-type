//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include <SFML/Graphics.hpp>
#include "../../../Commons/src/Event/Listener.h"
#include "../Graphic/Element.h"
#include "Widget.h"
#include "TextEdit.h"

Widget::TextEdit::TextEdit() :
    Widget(), _event(NULL), _element(NULL) {
}

Widget::TextEdit::TextEdit(std::string const& text) :
    Widget(), _event(NULL), _element(NULL), _text(text) {
}

Widget::TextEdit::~TextEdit() {    
}

std::string const&  Widget::TextEdit::getText() const {
    return _text;
}

void    Widget::TextEdit::setText(std::string const& text) {
    _text = text;
}

void    Widget::TextEdit::setText(const char* text) {
    _text = text;
}

void Widget::TextEdit::setPosition(const Vec2 &position) {
    _position = position;
}

void Widget::TextEdit::setSize(const Vec2 &size) {
    _size = size;
}

Vec2 const &Widget::TextEdit::getPosition(void) const {
    return _position;
}

Vec2 const &Widget::TextEdit::getSize(void) const {
    return _size;
}

Graphic::Element *Widget::TextEdit::getElement() {
    return &_element;
}