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

void    Widget::Table::addLine() {
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
    if (pos < _widgets.size()) {
        _widgets[pos].push_back(widget);
        widget->setPosition(Vec3(getPosition().x + pos,
                                 getPosition().y + _widgets[pos].size(),
                                 0.990));
    }
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

/*
void    Widget::Table::addColumn(Label* label) {
    uint32 sizeColumn = 0;
    
    for (std::map<Label*, std::vector<GraphicWidget*> >::iterator it = _widgets.begin(); it != _widgets.end(); ++it)
        sizeColumn += (*it).first->getText().size();
    label->setPosition(Vec3(getPosition().x + sizeColumn,
                            getPosition().y));
    _widgets[label] = std::vector<GraphicWidget*>();
    limit += 0.5;
}

void    Widget::Table::addWidget(Label* label, GraphicWidget* widget) {
    _widgets[label].push_back(widget);
    widget->setPosition(Vec3(label->getPosition().x,
                             getPosition().y - _widgets[label].size() - limit,
                             0.990));
}

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

std::vector<Widget::GraphicWidget*> const& Widget::Table::getColumn(Label* label) {
    return _widgets[label];
}

uint32  Widget::Table::getMaxLine() const {
    std::map<Label*, std::vector<GraphicWidget*> >::const_iterator it;
    uint32   max = 0;
    uint32   ret = 0;
    
    for (it = _widgets.begin(); it != _widgets.end(); ++it) {
        if (max < (*it).first->getSize().x)
            max = (*it).first->getSize().x;
        for (std::vector<GraphicWidget*>::const_iterator ite = (*it).second.begin();
            ite != (*it).second.end(); ++ite) {
            if (max < (*ite)->getSize().x)
                max = (*ite)->getSize().x;
        }
        std::cout << max << std::endl;
        ret += max + 1;
        max = 0;
    }
    std::cout << ret << std::endl;
    return ret;
}

void    Widget::Table::align(Align a, Label* column) {
    std::vector<GraphicWidget*>&   v = _widgets[column];
    uint32 i = 1;
    uint32 minsize = v[0]->getSize().x;
    uint32 maxsize = v[0]->getSize().x;
    
    for (std::vector<GraphicWidget*>::iterator it = v.begin();
         it != v.end(); ++it){
        if (minsize > (*it)->getSize().x)
            minsize = (*it)->getSize().x;
        if (maxsize < (*it)->getSize().x)
            maxsize = (*it)->getSize().x;
    }
    for (std::vector<GraphicWidget*>::iterator it = v.begin();
         it != v.end(); ++it) {
        if (a == CENTER) {
            (*it)->setPosition(Vec3((*it)->getPosition().x,
                                getPosition().y - i));
        } else if (a == LEFT) {
            (*it)->setPosition(Vec3((*it)->getPosition().x -
                                ((maxsize /2) - ((*it)->getSize().x / 2)),
                                    getPosition().y - i));
        } else {
            (*it)->setPosition(Vec3((*it)->getPosition().x +
                                ((maxsize /2) - ((*it)->getSize().x / 2)),
                                    getPosition().y - i));
        }
        i++;
    }
}
*/