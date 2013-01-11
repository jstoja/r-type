//
//  Graphic.cpp
//  R-Type
//
//  Created by Franck Lavisse on 03/01/2013
//
//

#include <SFML/Graphics.hpp>

#include <Application.h>
#include "Debug.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"
#include "Widgets/Button.h"
#include "Widgets/CheckBox.h"
#include "Widgets/Label.h"
#include "Widgets/TextEdit.h"

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        
        //_comboBox.putInScene(_scene);
        _button = new Widget::Button(&_scene,
                                     NULL,
                                     Vec2(1,1),
                                     Vec2(6,8),
									 Application::getInstance().getResourcesPath() + std::string("click.png"));
        //_scene.addElement(_button.getElement());
        
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::PointerPushed, _button->getElement()->getRect(), this));
		Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            Graphic::Renderer::getInstance().render();
        }
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
    }
    
private:
    Widget::Button*     _button;
    bool                _close;
    Graphic::Scene      _scene;
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
