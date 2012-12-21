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
#include "Graphic/Scene.h"

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _renderer(), _scene(), _button() {
        
        // Setup renderer
        _renderer.setScene(&_scene);
        
        // Setup scene
        _button.setPosition(Vec2(2, 2));
        _button.setSize(Vec2(1, 1));
        _scene.addElement(&_button);
        
        // Add event listeners
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::PointerIn
                                              | Event::PointerOut
                                              | Event::PointerMove
                                              | Event::PointerPushed
                                              | Event::PointerReleased,
                                              _renderer.sceneToViewport(_button.getRect()),
                                              this));
        
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            _renderer.render();
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
            Log("Move: " << _renderer.viewportToScene(event.pos));
        } else {
            Log("Event: " << event.type << " at " << event.pos);
        }
    }

private:
    bool                _close;
    Graphic::Renderer   _renderer;
    Graphic::Scene      _scene;
    Graphic::Element    _button;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}