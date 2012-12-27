//
//  CheckBox.cpp
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//

#include "Widget.h"
#include "Button.h"
#include "CheckBox.h"

Widget::CheckBox::CheckBox(bool checked) : Widget(),
    _checked(checked), _button() {
    _button.loadImage("checkbox.png");
}

Widget::CheckBox::~CheckBox() {
}

void    Widget::CheckBox::init() {
    _button.loadImage("checkbox.png");
    setPosition(Vec2(3,3));
    setSize(Vec2(3,3));
}

bool    Widget::CheckBox::isChecked() const {
    return _checked;
}

void    Widget::CheckBox::setChecked(bool checked) {
    _checked = checked;
}

void    Widget::CheckBox::update() {
    if (_checked) {
        _button.setCurrentFrame(1);
    } else {
        _button.setCurrentFrame(0);
    }
}

void    Widget::CheckBox::setSize(Vec2 const& v) {
    _button.setSize(v);
    _size = v;
}

void    Widget::CheckBox::setPosition(Vec2 const& v) {
    _button.setPosition(v);
    _position = v;
}
