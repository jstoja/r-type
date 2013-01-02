//
//  CheckBox.cpp
//  R-Type
//
//  Created by Franck Lavisse on 27/12/12.
//
//
#include "../Graphic/Sprite.h"
#include "Widget.h"
#include "Button.h"
#include "CheckBox.h"

Widget::CheckBox::CheckBox(bool checked) : Widget(),
    _checked(checked), _button() {
}

Widget::CheckBox::~CheckBox() {
}

Widget::CheckBox::CheckBox(Vec2 const& size,
                           Vec2 const& position,
                           bool checked) :  Widget(),
                                            _checked(checked),
                                            _button() {
    setSize(size);
    setPosition(position);
}

void    Widget::CheckBox::init() {
    _button.loadImage("checkbox.png");
    _element = *_button.getElement();
    _element.getSprite()->addFrame(Graphic::Sprite::Frame(Vec2(0,0.5),
                                                          Vec2(1,1)));
    _element.getSprite()->addFrame(Graphic::Sprite::Frame(Vec2(0,0),
                                                          Vec2(1,0.5)));
    _element.setCurrentFrame(1);
}

bool    Widget::CheckBox::isChecked() const {
    return _checked;
}

void    Widget::CheckBox::setChecked(bool checked) {
    _checked = checked;
}

void    Widget::CheckBox::update() {
    if (_checked) {
        _element.setCurrentFrame(2);
    } else {
        _element.setCurrentFrame(1);
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