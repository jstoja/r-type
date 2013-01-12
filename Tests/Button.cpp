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
#include "Widgets/Widget.h"
#include "Widgets/GraphicWidget.h"
#include "Widgets/Button.h"
#include "Application.h"

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate,
             public Widget::IButtonDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        _button = new Widget::Button(&_scene,
                                     this,
                                     _scene.getViewport()/10,
                                     _scene.getViewport()/2,
                                     "button.png",
                                     NULL);

        // Setup scene
      
        // Add event listeners
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));

        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            Graphic::Renderer::getInstance().render();
            sleep(1);
            _button->setSize(_button->getSize()+0.1);
        }
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        } 
    }

    virtual void buttonHovered(Widget::Button &instance) {}
    virtual void buttonUnHovered(Widget::Button &instance) {}
    virtual void buttonPushed(Widget::Button &instance) {}
    virtual void buttonReleased(Widget::Button &instance) {}

private:
    bool                _close;
    Graphic::Scene      _scene;
    //Graphic::Element    _button;
	Widget::Button*		_button;
};

int	main(int argc, char *argv[]) {
    try {
        Application::getInstance().init(argc, argv);
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
