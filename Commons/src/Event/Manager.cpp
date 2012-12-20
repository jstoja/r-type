//
//  Manager.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include <algorithm>

#include "Manager.h"
#include "Event.h"

Event::Manager::Manager() : _providers() {
    
}

Event::Manager::~Manager() {
    
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

void Event::Manager::processEvents() {
    for (std::vector<IProvider*>::iterator it = _providers.begin(),
         end = _providers.end(); it != end; ++it) {
        (*it)->processEvents(this);
    }
}

void Event::Manager::fire(Event const& event) {
    for (std::vector<Listener*>::iterator it = _listeners.begin(),
         end = _listeners.end(); it != end; ++it) {
        Listener* listener = *it;
        if (listener->getType() == event.type) {
            listener->processEvent(event);
        }
    }
}