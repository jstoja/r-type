//
// Table.cpp
// R-Type
//
// Created by Franck Lavisse on 10/01/13.
//
//
#include <SFML/Graphics.hpp>

#include <Application.h>

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Widget/Widget.h"
#include "Widget/GraphicWidget.h"
#include "Widget/Button.h"
#include "Widget/CheckBox.h"
#include "Widget/Label.h"
#include "Widget/Table.h"

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);

		Widget::Table	*table = new Widget::Table(2, "", &_scene);

		// Add event listeners
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
        }
    }
    
private:
    Widget::Table       *_table;
    bool                _close;
    Graphic::Scene      _scene;
};

int	main(int argc, char *argv[]) {
    try {
		App.init(argc, argv);
		App.setRelativeResourcesPath("../Client/Resources");
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}

