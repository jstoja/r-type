//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//
#include "Listener.h"
#include "Element.h"
#include "Widget.h"
#inckude "ByteArray.h"
#include "TextEdit.h"

Widget::TextEdit() : Widget() {
}

Widget::TextEdit(std::string const& text) _text(text) {
}


Widget::~Widget() {
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

Graphic::Element *Widget::TextEdit::getElement() {
    return &_element;
}