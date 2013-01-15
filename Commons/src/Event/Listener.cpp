//
//  Listener.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Listener.h"
#include "IListenerDelegate.h"

Event::Listener::Listener(uint32 type, IListenerDelegate* delegate)
: _type(static_cast<Type>(type)), _delegate(delegate), _rect(), _hasRect(false) {
}

Event::Listener::Listener(uint32 type, Rect2 const& rect, IListenerDelegate* delegate)
: _type(static_cast<Type>(type)), _delegate(delegate), _rect(rect), _hasRect(true) {
}

Event::Listener::~Listener() {
    
}


Event::Type Event::Listener::getType() const {
    return _type;
}

void Event::Listener::processEvent(Event const& event) {
    if (_delegate)
        _delegate->processEvent(event);
}

Rect2 const& Event::Listener::getRect() const {
    return _rect;
}

void        Event::Listener::setRect(Rect2 const& rect) {
    _rect = rect;
}

bool Event::Listener::hasRect() const {
    return _hasRect;
}
