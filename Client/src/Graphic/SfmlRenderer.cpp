//
//  Renderer.cpp
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#include "Renderer.h"
#include "Debug.hpp"

#ifdef GRAPHIC_RENDERER_SFML

Graphic::Renderer::Settings::Settings(std::string const& title,
                                      Vec2 size,
                                      uint32 antialiasingLevel,
                                      bool fullScreen)
: title(title), size(size), antialiasingLevel(antialiasingLevel), fullScreen(fullScreen) {
}

Graphic::Renderer::Renderer(Settings const& settings)
: _antialiasingLevel(0), _window(NULL) {
    
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
}

#endif