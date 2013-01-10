//
// Table.cpp
// R-Type
//
// Created by Franck Lavisse on 10/01/13.
//
//
#include <SFML/Graphics.hpp>
#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Widgets/Widget.h"
#include "Widgets/Label.h"
#include "Widgets/Table.h"

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        Widget::Label*  c1 = new Widget::Label(&_scene, "test1");
        Widget::Label*  c2 = new Widget::Label(&_scene, "test2");
        Widget::Label*  c3 = new Widget::Label(&_scene, "test3");

        
        c1->setSize(Vec2(5,1));
        c1->init();
        c2->setSize(Vec2(5,1));
        c2->init();
        c3->setSize(Vec2(5,1));
        c3->init();
        _table = new Widget::Table(&_scene);
        _table->setPosition(Vec2(2,6));
        _table->addColumn(c1);
        _table->addColumn(c2);
        _table->addColumn(c3);
        
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
        }
    }
    
private:
    Widget::Table       *_table;
    bool                _close;
    Graphic::Scene      _scene;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}

