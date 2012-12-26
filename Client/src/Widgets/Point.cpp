//
//  WPoint.cpp
//  R-Type
//
//  Created by Franck Lavisse on 25/12/12.
//
//

#include "Point.h"

Widget::Point::Point() {
}

Widget::Point::Point(uint32 x, uint32 y) {
    setX(x);
    setY(y);
}

Widget::Point::Point(Point const& cpy) {
    setX(cpy.getX());
    setY(cpy.getY());
}

Widget::Point::~Point() {
}

uint32  Widget::Point::getX() const {
    return _x;
}

uint32  Widget::Point::getY() const {
    return _y;
}

void    Widget::Point::setX(uint32 x) {
    _x = x;
}

void    Widget::Point::setY(uint32 y) {
    _y = y;
}

Widget::Point   Widget::Point::operator=(Widget::Point const& cpy) {
    setX(cpy.getX());
    setY(cpy.getY());
    return *this;
}

bool    Widget::Point::operator==(Widget::Point const& cmp) const {
    return (getX() == cmp.getX() && getY() == cmp.getY());
}

bool    Widget::Point::operator!=(Widget::Point const& cmp)  const {
    return (getX() != cmp.getX() || getY() != cmp.getY());
}