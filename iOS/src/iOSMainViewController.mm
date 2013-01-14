//
//  iOSMainViewController.mm
//  R-Type
//
//  Created by Gael du Plessix on 13/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "iOSMainViewController.h"

iOSMainViewController::iOSMainViewController(void) :
_viewController(NULL), _events() {
    Event::Manager::getInstance().registerProvider(this);
}

iOSMainViewController::~iOSMainViewController(void) {
    
}

void iOSMainViewController::setViewController(ViewController* viewController) {
    _viewController = viewController;
}

void iOSMainViewController::processEvents(Event::Manager* manager) {
    
}

void iOSMainViewController::pushEvent(Event::Event& event) {
    event.sender = this;
    _events.push(event);
}

GLKView* iOSMainViewController::getOpenGLView(void) const {
    return (GLKView*)_viewController.view;
}