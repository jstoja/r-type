//
//  Widget.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#include "Graphic/Image.h"
#include "Vec2.h"
#include "Graphic/Scene.h"
#include "Graphic/Texture.h"
#include "Widget.h"

Widget::Widget::Widget(Widget* parent)
    : _parent(parent), _focus(false), _visible(true) {
}

Widget::Widget::~Widget() {
}

void    Widget::Widget::setFocus(bool focus) {
    _focus = focus;
}

bool    Widget::Widget::hasFocus() const {
    return _focus;
}

void    Widget::Widget::setPosition(Vec3 const& v) {
    _position = v;
}

void    Widget::Widget::setSize(Vec2 const& v) {
    _size = v;
}

Vec2 const&   Widget::Widget::getSize() const {
    return _size;
}

Vec3 const&   Widget::Widget::getPosition() const {
    return _position;
}

Widget::Widget*  Widget::Widget::getParent() const {
    return _parent;
}

void Widget::Widget::setVisible(bool visible) {
	_visible = visible;
}

bool Widget::Widget::isVisible() const {
	return (_visible);
}
