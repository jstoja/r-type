//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#include "Widget.h"

Widget::Object::Object(Object* parent) {
    _parent = parent;
}

Widget::Object::~Object() {
}

uint32    Widget::Object::getId() const {
    return _id;
}

void    Widget::Object::setFocus(bool focus) {
    _focus = focus;
}

bool    Widget::Object::isFocus() const {
    return _focus;
}