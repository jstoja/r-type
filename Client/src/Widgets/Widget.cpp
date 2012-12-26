//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

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

bool    Widget::Widget::isFocus() const {
    return _focus;
}

void    Widget::Widget::setPosition(Vec2 const& v) {
    _position = v;
}

void    Widget::Widget::setSize(Vec2 const& v) {
    _size = v;
}

Vec2 const&   Widget::Widget::getSize() const {
    return _size;
}

Vec2 const&   Widget::Widget::getPosition() const {
    return _position;
}

