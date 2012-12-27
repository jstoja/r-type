//
//  Label.cpp
//  R-Type
//
//  Created by Franck Lavisse on 26/12/12
//
//
#include "Debug.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"
#include "Widgets/Widget.h"
#include "Widgets/Button.h"
#include "Widgets/CheckBox.h"

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
		_box = Widget::CheckBox();
        _box.init();
        _scene.addElement(_box.getElement());
        
         // Add event listeners
         Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
         Event::Manager::getInstance().addEventListener(new Event::Listener(Event::PointerIn
         | Event::PointerOut
         | Event::PointerMove
         | Event::PointerPushed
         | Event::PointerReleased,
         _box.getElement()->getRect(),
         this));
         
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
        } else if (event.type & Event::PointerIn) {
            std::cerr << "Pointer in" << std::endl;
        } else if (event.type & Event::PointerOut) {
            std::cerr << "Pointer out " << std::endl;
        } else if (event.type & Event::PointerPushed) {
            _box.setChecked(!_box.isChecked());
            _box.update();
            std::cerr << "Pointer pushed" << std::endl;
        } else if (event.type & Event::PointerReleased) {
            std::cerr << "Pointer released" << std::endl;
        }
    }
    
private:
    bool                _close;
    Graphic::Scene      _scene;
    Widget::CheckBox    _box;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}

