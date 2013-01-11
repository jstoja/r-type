//
//  Event.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Event.h"

Event::Event::Event(Type type, IProvider* sender)
: type(type), sender(sender), pos(), value('\0') {
}

Event::Event::Event(Type type, Vec2 const& pos, IProvider* sender)
: type(type), sender(sender), pos(pos), value('\0') {
}

Event::Event::Event(Type type, uint8 value, IProvider* sender)
: type(type), sender(sender), pos(), value(value) {
}