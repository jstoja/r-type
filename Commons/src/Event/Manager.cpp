//
//  Manager.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include <algorithm>

#include "Debug.h"
#include "Manager.h"
#include "Event.h"

template <> Event::Manager Singleton<Event::Manager>::_instance;

Event::Manager::Manager(void) : _providers(), _listeners(), _lastPointerPos() {
}

Event::Manager::~Manager(void) {
}

void Event::Manager::registerProvider(IProvider *provider) {
    if (std::find(_providers.begin(), _providers.end(), provider) == _providers.end()) {
        _providers.push_back(provider);
    }
}

void Event::Manager::addEventListener(Listener *listener) {
    if (std::find(_listeners.begin(), _listeners.end(), listener) == _listeners.end()) {
        _listeners.push_back(listener);
    }
}

void Event::Manager::processEvents(void) {
    for (std::vector<IProvider*>::iterator it = _providers.begin(),
         end = _providers.end(); it != end; ++it) {
        (*it)->processEvents(this);
    }
}

void Event::Manager::fire(Event const& event) {
    for (std::vector<Listener*>::iterator it = _listeners.begin(),
         end = _listeners.end(); it != end; ++it) {
        Listener* listener = *it;
        if ((listener->getType() & event.type)
            && (!listener->hasRect() || listener->getRect().in(event.pos))) {
            listener->processEvent(event);
        }
        
        // Pointer in/out events
        if ((event.type & PointerMove) && (listener->getType() & PointerIn)
            && !listener->getRect().in(_lastPointerPos)
            && listener->getRect().in(event.pos)) {
            listener->processEvent(Event(PointerIn, event.pos, event.sender));
        }
        if ((event.type & PointerMove) && (listener->getType() & PointerOut)
            && listener->getRect().in(_lastPointerPos)
            && !listener->getRect().in(event.pos)) {
            listener->processEvent(Event(PointerOut, event.pos, event.sender));
        }
    }
 
    if (event.type == PointerMove)
        _lastPointerPos = event.pos;
}