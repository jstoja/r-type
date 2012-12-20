//
//  Listener.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Listener.h"
#include "IListenerDelegate.h"

Event::Listener::Listener(Type type, IListenerDelegate* delegate)
: _type(type), _delegate(delegate), _rect() {
}

Event::Listener::Listener(Type type, Rect const& rect, IListenerDelegate* delegate)
: _type(type), _delegate(delegate), _rect(rect) {
}

Event::Type Event::Listener::getType() const {
    return _type;
}

void Event::Listener::processEvent(Event const& event) {
    if (_delegate)
        _delegate->processEvent(event);
}

Rect const& Event::Listener::getRect() const {
    return _rect;
}