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
#include "Manager.h"

Widget::Widget::Widget(Widget* parent)
    : _parent(parent), _focus(false), _visible(true),
	_needUpdate(true), _needDelete(false) {
	Manager::getInstance().registerWidget(this);
}

Widget::Widget::~Widget() {
	Manager::getInstance().unregisterWidget(this);
}

void Widget::Widget::deleteLater() {
	_needDelete = true;
}

bool Widget::Widget::needDelete() const {
	return (_needDelete);
}

void    Widget::Widget::setFocus(bool focus) {
    _focus = focus;
	setNeedUpdate(true);
}

bool    Widget::Widget::hasFocus() const {
    return _focus;
}

void    Widget::Widget::setPosition(Vec3 const& v) {
    _position = v;
	_rect = Rect2(_position - Vec3(_size.x / 2, _size.y / 2), _size);
	setNeedUpdate(true);
}

void    Widget::Widget::setSize(Vec2 const& v) {
    _size = v;
	_rect = Rect2(_position - Vec3(_size.x / 2, _size.y / 2), _size);
	setNeedUpdate(true);
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
	if (_visible != visible) {
		_visible = visible;
		setNeedUpdate(true);
	}
}

bool Widget::Widget::isVisible() const {
	return (_visible);
}

void Widget::Widget::update() {
}

bool Widget::Widget::needUpdate() {
	return (_needUpdate);
}

void Widget::Widget::setNeedUpdate(bool value) {
	_needUpdate = value;
}

Rect2 const&	Widget::Widget::getRect() const {
	return (_rect);
}
