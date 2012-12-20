//
//  Event.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Event.h"

Event::Event::Event(Type type, IProvider* sender)
: type(type), sender(sender), rect() {
}

Event::Event::Event(Type type, Rect const& rect, IProvider* sender)
: type(type), sender(sender), rect(rect) {
}