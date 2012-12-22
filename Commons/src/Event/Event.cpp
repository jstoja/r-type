//
//  Event.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Event.h"

Event::Event::Event(Type type, IProvider* sender)
: type(type), sender(sender), pos() {
}

Event::Event::Event(Type type, Vec2 const& pos, IProvider* sender)
: type(type), sender(sender), pos(pos) {
}