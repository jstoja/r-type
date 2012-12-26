//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

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