//
//  Graphic.cpp
//  R-Type
//
//  Created by Franck Lavisse on 03/01/2013
//
//

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
#include "Widgets/ComboBox.h"
#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        
        _comboBox = Widget::ComboBox();
        _comboBox.push(std::string("marseille"), Vec2(6,5), this);
        _comboBox.push(std::string("molotov"), Vec2(6,6), this);
        _comboBox.push(std::string("noob"), Vec2(6,7), this);
        _comboBox.putInScene(_scene);
        _button = Widget::Button(Vec2(1,1),
                                 Vec2(6,8),
                                 std::string("click.png"));
        _scene.addElement(_button.getElement());
        
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::PointerPushed, _button.getElement()->getRect(), this));
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
        }  else if (event.type & Event::PointerPushed) {
            _comboBox.updateEvent(event);
            if (_button.getElement()->getRect().in(event.pos)) {
                _comboBox.uncheck();
            }
        }
    }
    
private:
    Widget::ComboBox    _comboBox;
    Widget::Button      _button;
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
