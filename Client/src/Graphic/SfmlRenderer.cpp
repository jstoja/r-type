//
//  Renderer.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Debug.h"
#include "Renderer.h"
#include "Manager.h"
#include "Event.h"

#ifdef GRAPHIC_RENDERER_SFML

void Graphic::Renderer::createContext(Settings const& settings) {    
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = settings.antialiasingLevel;
    contextSettings.majorVersion = 2;
    contextSettings.minorVersion = 1;
    
    // Create the SFML Window
    _window = new sf::Window(sf::VideoMode(settings.size.x, settings.size.y),
                             settings.title,
                             settings.fullScreen ? sf::Style::Fullscreen : sf::Style::Default,
                             contextSettings);
    
    contextSettings = _window->getSettings();
    _antialiasingLevel = contextSettings.antialiasingLevel;
    
    Log("OpenGL Version " << contextSettings.majorVersion << "." << contextSettings.minorVersion
        << ", Antialiasing level: " << _antialiasingLevel);
}

Graphic::Renderer::~Renderer() {
    if (_window)
        delete _window;
    destruct();
}

void Graphic::Renderer::processEvents(Event::Manager* manager) {
    sf::Event sfEvent;
    
    Event::PointerButton pointerButtonValues[] =
    {(Event::PointerButton)sf::Mouse::Left,
        (Event::PointerButton)sf::Mouse::Right,
        (Event::PointerButton)sf::Mouse::Middle
    };
    
    while (_window->pollEvent(sfEvent)) {
        if (sfEvent.type == sf::Event::Closed) {
            manager->fire(Event::Event(Event::Close, this));
        } else if (sfEvent.type == sf::Event::MouseMoved) {
            manager->fire(Event::Event(Event::PointerMove,
                                       viewportToScene(Vec2(sfEvent.mouseMove.x,
                                                            sfEvent.mouseMove.y)),
                                       this));
        } else if (sfEvent.type == sf::Event::MouseButtonPressed
                   || sfEvent.type == sf::Event::MouseButtonReleased) {
            Event::Event event(sfEvent.type == sf::Event::MouseButtonPressed ?
                               Event::PointerPushed : Event::PointerReleased);
            event.pointerButton = pointerButtonValues[sfEvent.mouseButton.button];
            event.pos = viewportToScene(Vec2(sfEvent.mouseButton.x, sfEvent.mouseButton.y));
            event.sender = this;
            manager->fire(event);
        }
        //! Update the viewport if window size has changed
        else if (sfEvent.type == sf::Event::Resized) {
            updateViewport();
        }
    }
}

Vec2 Graphic::Renderer::getViewportSize(void) const {
    sf::Vector2u size = _window->getSize();
    return Vec2(size.x, size.y);
}

void Graphic::Renderer::refresh(void) {
    _window->display();
}

#endif