//
//  Graphic.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Debug.h"
#include "Application.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"
#include "Graphic/Image.h"

#include "Menu/WelcomeMenu.h"
#include "Menu/IMenuDelegate.h"

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate, public Menu::IMenuDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);

        // Setup scene
        Graphic::Image image;
        
        Graphic::Scenery* scenery;
        Graphic::Texture* texture;
        
        // Create sceneries
        image.loadFromResource("background.png");
        texture = new Graphic::Texture();
        texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        scenery = new Graphic::Scenery();
        scenery->setTexture(texture);
        scenery->setRange(Vec2(0, 1000));
        scenery->setWidth(16);
        scenery->setSpeed(0);
        scenery->setDepth(0.999);
        _scene.addScenery(scenery);
        
        image.loadFromResource("stars-deep.png");
        texture = new Graphic::Texture();
        texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        scenery = new Graphic::Scenery();
        scenery->setTexture(texture);
        scenery->setRange(Vec2(0, 1000));
        scenery->setWidth(16);
        scenery->setSpeed(0.2);
        scenery->setDepth(0.998);
        scenery->setOpacity(0.2);
        _scene.addScenery(scenery);
        
        image.loadFromResource("stars-blue.png");
        texture = new Graphic::Texture();
        texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        scenery = new Graphic::Scenery();
        scenery->setTexture(texture);
        scenery->setRange(Vec2(0, 1000));
        scenery->setWidth(16);
        scenery->setSpeed(0.8);
        scenery->setDepth(0.997);
        _scene.addScenery(scenery);

        image.loadFromResource("stars-red.png");
        texture = new Graphic::Texture();
        texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        scenery = new Graphic::Scenery();
        scenery->setTexture(texture);
        scenery->setRange(Vec2(0, 1000));
        scenery->setWidth(16);
        scenery->setSpeed(1.2);
        scenery->setDepth(0.996);
        _scene.addScenery(scenery);
                
        image.loadFromResource("planets.png");
        texture = new Graphic::Texture();
        texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
        scenery = new Graphic::Scenery();
        scenery->setTexture(texture);
        scenery->setRange(Vec2(0, 1000));
        scenery->setWidth(3 * 16);
        scenery->setSpeed(0.5);
        scenery->setDepth(0.995);
        scenery->setOpacity(0.8);
        _scene.addScenery(scenery);

        _wmenu = new Menu::WelcomeMenu(&_scene, this);

        // Add event listeners
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        
        float32 xPos = 0;
        
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            Graphic::Renderer::getInstance().render();
            
            //_scene.setViewportPosition(Vec2(100 + sin(xPos)*10, 0));
            _scene.setViewportPosition(Vec2(xPos, 0));
            
            xPos += 0.02;

            //usleep(10000);
        }
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        }
    }

    virtual void welcomeCompleted() {
        _close = true;
    }

private:
    Menu::WelcomeMenu   *_wmenu;
    bool                _close;
    Graphic::Scene      _scene;
};

int	main(int argc, char *argv[]) {
    try {
        // Setup application
        Application::getInstance().init(argc, argv);
        
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
