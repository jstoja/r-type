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

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _renderer(), _scene(), _button() {
        
        // Setup renderer
        _renderer.setScene(&_scene);
        
        // Setup scene
        _button.setPosition(Vec2(8, 4.5));
        _button.setSize(Vec2(3, 1));
        
        sf::Image image;
        image.loadFromFile("button.png");
        
        Graphic::Texture* buttonTexture = new Graphic::Texture();
        buttonTexture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        Graphic::Sprite* buttonSprite = new Graphic::Sprite();
        buttonSprite->setTexture(buttonTexture);
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0, 0.33)));
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.33), Vec2(1.0, 0.66)));
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.66), Vec2(1.0, 1)));
        
        _button.setSprite(buttonSprite);
        _button.setCurrentFrame(0);
        
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
                                              _button.getRect(),
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
        } else if (event.type & Event::PointerIn) {
            _button.setCurrentFrame(2);
        } else if (event.type & Event::PointerOut) {
            _button.setCurrentFrame(0);
        } else if (event.type & Event::PointerPushed) {
            _button.setCurrentFrame(1);
        } else if (event.type & Event::PointerReleased) {
            _button.setCurrentFrame(2);
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