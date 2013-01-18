//
// WidgetManager.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  ven. janv. 18 16:02:52 2013 Samuel Olivier
//

#include "Manager.h"

template<> Widget::Manager *Singleton<Widget::Manager>::_instance = new Widget::Manager();

Widget::Manager::Manager() {
}

Widget::Manager::~Manager() {
}

void	Widget::Manager::registerWidget(Widget* widget) {
	_widgets.push_back(widget);
}

void	Widget::Manager::unregisterWidget(Widget* widget) {
    if (!widget->needDelete())
        _widgets.remove(widget);
}

void	Widget::Manager::update() {
	for (std::list<Widget*>::iterator it = _widgets.begin(); it != _widgets.end();) {
		if ((*it)->needDelete()) {
			delete *it;
			it = _widgets.erase(it);
			continue;
		}
		if ((*it)->isVisible() && (*it)->needUpdate()) {
			(*it)->setNeedUpdate(false);
			(*it)->update();
		}
		++it;
	}
}