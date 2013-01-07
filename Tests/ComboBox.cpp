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
#include "Widgets/ComboBox.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include "Types.h"
#include "Graphic/Texture.h"
#include "Graphic/Sprite.h"
#include "Graphic/Font.h"
#include "Widgets/Label.h"

#include <SFML/Graphics.hpp>

class Test : public Event::IListenerDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        _comboBox = new Widget::ComboBox(&_scene);
        std::string text1("marseille");
        std::string text2("molotov");
        std::string text3("noob");
        _comboBox->push(text1, Vec2(6,5), this);
        _comboBox->push(text2, Vec2(6,6), this);
        _comboBox->push(text3, Vec2(6,7), this);
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
        _comboBox->updateEvent(event);
        std::cerr << "Pointer pushed" << std::endl;
    } else if (event.type & Event::PointerReleased) {
        std::cerr << "Pointer released" << std::endl;
    }
}

private:
    bool                _close;
    Graphic::Scene      _scene;
    Widget::ComboBox*   _comboBox;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
