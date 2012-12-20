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
        .addEventListener(new Event::Listener(Event::PointerIn,
                                              Rect(100, 100, 100, 100),
                                              this));
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::PointerOut,
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