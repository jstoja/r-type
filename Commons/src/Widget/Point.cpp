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
    setX(cpy.x());
    setY(cpy.y());
}

Widget::Point::~Point() {
}

uint32  Widget::Point::x() const {
    return _x;
}

uint32  Widget::Point::y() const {
    return _y;
}

void    Widget::Point::setX(uint32 x) {
    _x = x;
}

void    Widget::Point::setY(uint32 y) {
    _y = y;
}

Widget::Point   Widget::Point::operator=(Widget::Point const& cpy) {
    setX(cpy.x());
    setY(cpy.y());
    return *this;
}

bool    Widget::Point::operator==(Widget::Point const& cmp) const {
    return (x() == cmp.x() && y() == cmp.y());
}

bool    Widget::Point::operator!=(Widget::Point const& cmp)  const {
    return (x() != cmp.x() || y() != cmp.y());
}