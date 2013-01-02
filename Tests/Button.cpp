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
#include "Widgets/Button.h"

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene(), _button() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
		_button = Widget::Button();
        
        // Setup scene
        _button.setPosition(Vec2(4,4));
        _button.setSize(Vec2(9, 3));
        _button.loadImage("button.png");
        
        _scene.addElement(_button.getElement());
      
        /*
        // Add event listeners
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::PointerIn
                                              | Event::PointerOut
                                              | Event::PointerMove
                                              | Event::PointerPushed
                                              | Event::PointerReleased,
                                              _button.getElement()->getRect(),
                                              this));
         */
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            Graphic::Renderer::getInstance().render();
        }
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        } /*else if (event.type & Event::PointerIn) {
            _button.setCurrentFrame(2);
        } else if (event.type & Event::PointerOut) {
            _button.setCurrentFrame(0);
        } else if (event.type & Event::PointerPushed) {
            _button.setCurrentFrame(1);
        } else if (event.type & Event::PointerReleased) {
            _button.setCurrentFrame(2);
        }*/
    }

private:
    bool                _close;
    Graphic::Scene      _scene;
    //Graphic::Element    _button;
	Widget::Button		_button;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
