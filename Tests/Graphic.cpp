//
//  Graphic.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _renderer() {
        
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::PointerIn
                                              | Event::PointerOut
                                              | Event::PointerMove
                                              | Event::PointerPushed
                                              | Event::PointerReleased,
                                              Rect(100, 100, 100, 100),
                                              this));

        
        while (!_close) {
            Event::Manager::getInstance().processEvents();
        }
        
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        } else if (event.type == Event::PointerIn) {
            Log("IN !");
        } else if (event.type == Event::PointerOut) {
            Log("OUT !");
        } else if (event.type == Event::PointerMove) {
            Log("Move: " << event.pos);
        } else {
            Log("Event: " << event.type << " at " << event.pos);
        }
    }

private:
    bool                _close;
    Graphic::Renderer   _renderer;
};

int	main(int argc, char *argv[]) {
    Test client;
    
	return (0);
}