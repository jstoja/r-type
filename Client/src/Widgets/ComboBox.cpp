//
//  ComboBox.cpp
//  R-Type
//
//  Created by Franck Lavisse on 02/01/13.
//
//

#include <SFML/Graphics.hpp>
#include "Widget.h"
#include "Button.h"
#include "../Graphic/Scene.h"
#include "../Graphic/Font.h"
#include "../../Commons/src/Event/Event.h"
#include "../../Commons/src/Event/Manager.h"
#include "../../Commons/src/Event/Listener.h"
#include "../../Commons/src/Event/IListenerDelegate.h"
#include "Label.h"
#include "CheckBox.h"
#include "ComboBox.h"

Widget::ComboBox::ComboBox(Graphic::Scene* scene,
                           Widget* parent) : Widget(scene, parent) {
    _items.resize(0);
}

Widget::ComboBox::ComboBox(Graphic::Scene* scene,
                           std::vector<Label*>& labels,
                           std::vector<CheckBox*>& checks,
                           Event::IListenerDelegate *delegate,
                           Widget* parent) :
    Widget(scene, parent) {
    if (labels.size() == checks.size()) {
        std::vector<Label*>::iterator it_label = labels.begin();
        std::vector<CheckBox*>::iterator it_check = checks.begin();

        for (; it_label != labels.end(); ++it_label, ++it_check)
            push(*it_check, *it_label, delegate);
    }
}

Widget::ComboBox::ComboBox(Graphic::Scene* scene,
                           std::vector<std::pair<CheckBox*,
                           Label*>* >& v,
                           Event::IListenerDelegate *delegate,
                           Widget* parent) :
    Widget(scene, parent) {
    for (std::vector<std::pair<CheckBox*, Label*>* >::iterator it = v.begin();
         it != v.end(); ++it)
        push((*it)->first, (*it)->second, delegate);
}


Widget::ComboBox::~ComboBox() {
    size_t limit = _items.size();
    for (size_t i = 0; i < limit; ++i) {
        delete _items[i]->first;
        delete _items[i]->second;
    }
}

void    Widget::ComboBox::update() {
    for (std::vector<std::pair<CheckBox*, Label*>* >::iterator it = _items.begin(); it != _items.end(); ++it) {
        (*it)->first->update();
        (*it)->second->update();
    }
}

Widget::Label*    Widget::ComboBox::getSelectedLabel() const {
    for (std::vector<std::pair<CheckBox*, Label*>* >::const_iterator it = _items.begin(); it != _items.end(); ++it) {
        if ((*it)->first->isChecked())
            return (*it)->second;
    }
    return NULL;
}

void    Widget::ComboBox::push(CheckBox *cb,
                               Label *l,
                               Event::IListenerDelegate *delegate) {
    std::pair<CheckBox*, Label*>    *p = new std::pair<CheckBox*, Label*>(cb, l);
    _items.push_back(p);
    Event::Manager::getInstance().addEventListener(new Event::Listener(Event::PointerIn | Event::PointerOut | Event::PointerMove | Event::PointerPushed| Event::PointerReleased,
        cb->getElement()->getRect(), delegate));
}

void    Widget::ComboBox::push(std::string const& name,
                               Vec2 const& pos,
                               Event::IListenerDelegate *delegate) {
    CheckBox    *check = new CheckBox(_scene, Vec2(1,1), pos);
    Label       *text = new Label(_scene, name);
    Vec2        size = text->getElementSize();
    text->setPosition(Vec2(pos.x + size.x / 2 + 1, pos.y));
    text->init();
    check->init();
    push(check, text, delegate);
}

void    Widget::ComboBox::updateEvent(Event::Event const& event) {
    for (std::vector<std::pair<CheckBox*, Label*>* >::iterator it = _items.begin(); it != _items.end(); ++it) {
        if ((*it)->first->getElement()->getRect().in(event.pos))
            (*it)->first->setChecked(!(*it)->first->isChecked());
        else
            (*it)->first->setChecked(false);
        (*it)->first->update();
    }
}

void    Widget::ComboBox::uncheck() {
    std::vector<std::pair<CheckBox*, Label*>* >::iterator it;
    
    for (it = _items.begin(); it != _items.end(); ++it)
        (*it)->first->setChecked(false);
}