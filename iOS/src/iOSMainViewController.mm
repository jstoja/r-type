//
//  iOSMainViewController.mm
//  R-Type
//
//  Created by Gael du Plessix on 13/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "iOSMainViewController.h"
#include "Debug.h"

iOSMainViewController::iOSMainViewController(void) :
_viewController(NULL), _events() {
}

iOSMainViewController::~iOSMainViewController(void) {
    
}

void iOSMainViewController::setViewController(ViewController* viewController) {
    _viewController = viewController;
}

ViewController* iOSMainViewController::getViewController(void) const {
    return _viewController;
}

void iOSMainViewController::processEvents(Event::Manager* manager) {
    while (_events.size() > 0) {
        manager->fire(_events.top());
        _events.pop();
    }
}

void iOSMainViewController::pushEvent(Event::Event& event) {
    // Register to the event manager
    // This can't be done in constructor because iOSMainViewController and
    // event manager both are singleton, so they can't use each other in their
    // constructors...
    static bool registered = false;
    if (!registered) {
        Event::Manager::getInstance().registerProvider(this);
        registered = true;
    }
    
    event.sender = this;
    _events.push(event);
}

GLKView* iOSMainViewController::getOpenGLView(void) const {
    return (GLKView*)_viewController.view;
}