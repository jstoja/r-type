//
//  main.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"

class Client : public Event::IListenerDelegate {
public:
    Client()
    : _close(false), _renderer() {
        
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        
        while (!_close) {
            Event::Manager::getInstance().processEvents();
        }
        
    }
    
    ~Client() {}
    
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
    Client client;
    
	return (0);
}