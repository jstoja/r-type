//
//  Table.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//
#include <SFML/Graphics.hpp>
#include "Widget.h"
#include "Label.h"
#include "../Graphic/Scene.h"
#include "Table.h"

Widget::Table::Table(Graphic::Scene* scene, Widget *parent) :
    Widget(scene, parent) {
}

Widget::Table::~Table() {
}

void    Widget::Table::addColumn(Label* label) {
    uint32 sizeColumn = 0;
    
    for (std::map<Label*, std::vector<Widget*> >::iterator it = _widgets.begin(); it != _widgets.end(); ++it)
        sizeColumn += (*it).first->getText().size();
    label->setPosition(Vec2(_position.x
                        + sizeColumn,
                        _position.y));
    _widgets[label] = std::vector<Widget*>();
}

void    Widget::Table::addWidget(Label* label, Widget* widget) {
    _widgets[label].push_back(widget);
    widget->setPosition(Vec2(label->getPosition().x,
                             label->getPosition().y - _widgets[label].size()));
}

std::vector<Widget::Widget*> const& Widget::Table::getColumn(Label* label){
    return _widgets[label];
}