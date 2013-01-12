//
//  Table.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//
#include <SFML/Graphics.hpp>
#include "Widget.h"
#include "GraphicWidget.h"
#include "Label.h"
#include "../Graphic/Scene.h"
#include "Table.h"

Widget::Table::Table(Widget *parent) :
    Widget(parent) {
}

Widget::Table::~Table() {
}

void    Widget::Table::addColumn(Label* label) {
    uint32 sizeColumn = 0;
    
    for (std::map<Label*, std::vector<Widget*> >::iterator it = _widgets.begin(); it != _widgets.end(); ++it)
        sizeColumn += (*it).first->getText().size();
    label->setPosition(Vec2(getPosition().x + sizeColumn,
                            getPosition().y));
    _widgets[label] = std::vector<Widget*>();
}

void    Widget::Table::addWidget(Label* label, Widget* widget) {
    _widgets[label].push_back(widget);
    widget->setPosition(Vec2(label->getPosition().x,
                             getPosition().y - _widgets[label].size()));
}

std::vector<Widget::Widget*> const& Widget::Table::getColumn(Label* label){
    return _widgets[label];
}

void    Widget::Table::align(Align a, Label* column) {
    std::vector<Widget*>&   v = _widgets[column];
    uint32 i = 1;
    uint32 minsize = v[0]->getSize().x;
    uint32 maxsize = v[0]->getSize().x;
    uint32 sp = 0;
    
    for (std::vector<Widget*>::iterator it = v.begin();
         it != v.end(); ++it){
        if (minsize > (*it)->getSize().x)
            minsize = (*it)->getSize().x;
        if (maxsize < (*it)->getSize().x)
            maxsize = (*it)->getSize().x;
    }
    std::cout << "maxsize " << maxsize << std::endl;
    for (std::vector<Widget*>::iterator it = v.begin();
         it != v.end(); ++it) {
        if (a == CENTER) {
            (*it)->setPosition(Vec2((*it)->getPosition().x,
                                getPosition().y - i));
        } else if (a == LEFT) {
            std::cout << "before move" << std::endl;
            std::cout << (*it)->getPosition().x << ' '
                      << (*it)->getPosition().y << ' '
                      << (*it)->getSize().x << ' ' << (*it)->getSize().y
            << std::endl;
            std::cout << ((*it)->getSize().x / 2) - (maxsize / 2) << std::endl;
            (*it)->setPosition(Vec2((*it)->getPosition().x -
                                ((maxsize /2) - ((*it)->getSize().x / 2)),
                                getPosition().y - i));
            std::cout << "after move" << std::endl;
            std::cout << (*it)->getPosition().x << ' '
                      << (*it)->getPosition().y << ' '
                      << (*it)->getSize().x << ' ' << (*it)->getSize().y
                      << std::endl;
        } else {
            (*it)->setPosition(Vec2((*it)->getPosition().x
                                    + (maxsize / 2),
                                getPosition().y - i));
        }
        i++;
    }
}