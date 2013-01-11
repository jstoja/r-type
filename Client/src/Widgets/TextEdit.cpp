//
//  TextEdit.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12.
//
//

#include "Widget.h"
#include "Label.h"
#include "TextEdit.h"

Widget::TextEdit::TextEdit(Graphic::Scene* scene,
                           Widget* parent) :
    Widget(scene, parent), _event(NULL), _label(scene, parent) {
}

Widget::TextEdit::TextEdit(Graphic::Scene* scene,
                           std::string const& text,
                           Widget* parent) :
    Widget(scene, parent), _event(NULL), _label(scene, parent) {
}

Widget::TextEdit::~TextEdit() {
}

std::string const&  Widget::TextEdit::getText() const {
    return _label.getText();
}

void    Widget::TextEdit::setText(std::string const& text) {
    _label.setText(text);
    update();
}

void    Widget::TextEdit::update() {
    _label.update();
    _element = *_label.getElement();
}

void    Widget::TextEdit::operator<<(char c) {
    _label << c;
    update();
}

void    Widget::TextEdit::operator<<(std::string const& str) {
    _label << str;
    update();
}

void    Widget::TextEdit::init() {
    _label.init();
}

void    Widget::TextEdit::setPosition(Vec2 const& v) {
    _position = v;
    _label.setPosition(v);
    update();
}

void    Widget::TextEdit::clear() {
    _label.clear();
}
