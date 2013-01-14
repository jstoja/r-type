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
    _space = 0.0;
}

Widget::Table::~Table() {
}

void    Widget::Table::addLine() {
    _space += 1;
    _widgets.push_back(std::vector<GraphicWidget*>());
}

std::vector<Widget::GraphicWidget*> Widget::Table::getLine(uint32 pos) {
    return _widgets[pos];
}

Widget::GraphicWidget*  Widget::Table::getWidget(uint32 x,
                                                 uint32 y) {
    return _widgets[x][y];
}

void    Widget::Table::addWidget(GraphicWidget* widget,
                                 uint32 pos) {
    uint32 sizeLine = getSizeLine(pos);
    _widgets[pos].push_back(widget);
    std::cout << "put widget in " << getPosition().x
                  << " " << getPosition().y + _widgets[pos].size()
        << std::endl;
    widget->setPosition(Vec3(getPosition().x + sizeLine,
                             getPosition().y - pos - _space,
                        0.990));
}

void    Widget::Table::align(Align alignement, uint32 pos) {
    uint32 i = 0;
    std::vector<GraphicWidget*>::iterator it;
    
    if (alignement == LEFT) {
        for (it = _widgets[pos].begin(); it != _widgets[pos].end(); ++it) {
            
        }
    } else if (alignement == RIGHT) {
        for (it = _widgets[pos].begin(); it != _widgets[pos].end(); ++it) {
            
        }
    } else {
        for (it = _widgets[pos].begin(); it != _widgets[pos].end(); ++it) {
            (*it)->setPosition(Vec3(getPosition().x + pos,
                                    getPosition().y + i,
                                    0.990));
            i++;
        }
    }
}

uint32  Widget::Table::getSizeLine(uint32 pos) const {
    std::vector<GraphicWidget*>::const_iterator it;
    uint32  ret = 0;
    
    for (it = _widgets[pos].begin(); it != _widgets[pos].end(); ++it) {
        ret += (*it)->getSize().x;
    }
    return ret;
}

void    Widget::Table::setLineBackground(uint32 pos,
                                         std::string const& name) {
    GraphicWidget*  w = _widgets[pos][0];
    uint32  sizeLine = getSizeLine(pos);
    
    w->createBackground(name);
    w->setBackgroundSize(Vec3(sizeLine,
                              w->getSize().y,
                              0.995));
    (void)name;
}

/*
void    Widget::Table::lineBackground(std::string const& name) {
    uint32 size = getMaxLine();
   _widgets.begin()->first->createBackground(name);
   _widgets.begin()->first->setBackgroundSize(Vec2(size, 1));
    std::map<Label*, std::vector<GraphicWidget*> >::iterator it = _widgets.begin();
    for (std::vector<GraphicWidget*>::iterator ite = (*it).second.begin() ;
         ite != (*it).second.end(); ++ite) {
        (*ite)->createBackground(name);
        (*ite)->setBackgroundSize(Vec2(size, 1));
    }
}


*/