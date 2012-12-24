//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#include "Widget.h"

Widget::Widget(Widget* parent) _parent(parent) {
}

Widget::~Widget() {
}

uint32    Widget::getId() const {
    return _id;
}

void    Widget::setFocus(bool focus) {
    _focus = focus;
}

bool    Widget::getFocus() const {
    return _focus;
}