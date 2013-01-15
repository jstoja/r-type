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

#ifndef OS_IOS
template <> Event::Manager* Singleton<Event::Manager>::_instance = new Event::Manager();
#endif

Event::Manager::Manager(void) : _providers(new std::vector<IProvider*>()), _listeners(new std::vector<Listener*>()),
	_lastPointerPos(), _isInListenerLoop(0), _listenersToRemove(new std::list<Listener*>()),
	_listenersToAdd(new std::list<Listener*>()){
}

Event::Manager::~Manager(void) {
	delete _providers;
	delete _listeners;
	delete _listenersToRemove;
	delete _listenersToAdd;
}

void Event::Manager::registerProvider(IProvider *provider) {
    if (std::find(_providers->begin(), _providers->end(), provider) == _providers->end()) {
        _providers->push_back(provider);
    }
}

void Event::Manager::addEventListener(Listener *listener) {
	if (_isInListenerLoop == 0) {
	    if (std::find(_listeners->begin(), _listeners->end(), listener) == _listeners->end())
		    _listeners->push_back(listener);
	} else
		_listenersToAdd->push_back(listener);
}

void Event::Manager::removeEventListener(Listener* listener) {
	if (_isInListenerLoop == 0) {
	    std::vector<Listener*>::iterator it =
		    std::find(_listeners->begin(), _listeners->end(), listener);
		if (it != _listeners->end())
			_listeners->erase(it);
	} else
		_listenersToRemove->push_back(listener);
}

void Event::Manager::processEvents(void) {
    for (std::vector<IProvider*>::iterator it = _providers->begin(),
         end = _providers->end(); it != end; ++it) {
        (*it)->processEvents(this);
    }
}

void Event::Manager::fire(Event const& event) {
	std::list<Listener*>	toDelete;
	++_isInListenerLoop;
    for (std::vector<Listener*>::iterator it = _listeners->begin(); it != _listeners->end(); ++it) {
        Listener* listener = *it;
        if ((listener->getType() & event.type)
            && (!listener->hasRect() || listener->getRect().in(event.pos))) {
            listener->processEvent(event);
        }
        // Pointer in/out events
        if (!listener->shouldBeDeleted() && (event.type & PointerMove) && (listener->getType() & PointerIn)
            && !listener->getRect().in(_lastPointerPos)
            && listener->getRect().in(event.pos)) {
            listener->processEvent(Event(PointerIn, event.pos, event.sender));
        }
        if (!listener->shouldBeDeleted() && (event.type & PointerMove) && (listener->getType() & PointerOut)
            && listener->getRect().in(_lastPointerPos)
            && !listener->getRect().in(event.pos)) {
            listener->processEvent(Event(PointerOut, event.pos, event.sender));
        }
		if (listener->shouldBeDeleted())
			toDelete.push_back(listener);
    }
	--_isInListenerLoop;
    if (event.type == PointerMove)
        _lastPointerPos = event.pos;
	_flushListeners();
	for (std::list<Listener*>::iterator it = toDelete.begin(); it != toDelete.end(); ++it)
		delete *it;
	toDelete.clear();
}

void Event::Manager::_flushListeners() {
	if (_isInListenerLoop == 0) {
		for (std::list<Listener*>::iterator it = _listenersToAdd->begin(); it != _listenersToAdd->end(); ++it)
			addEventListener(*it);
		_listenersToAdd->clear();
	}
	if (_isInListenerLoop == 0) {
		for (std::list<Listener*>::iterator it = _listenersToRemove->begin(); it != _listenersToRemove->end(); ++it)
			removeEventListener(*it);
		_listenersToRemove->clear();
	}
}
