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
    : _close(false), _scene(), _label() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        

        
        //
        
        std::string str("Coucou_Karina");
		_label = Widget::Label(str);
    
        // Setup scene
        _label.setPosition(Vec2(7,7));
        _label.setSize(Vec2(str.length(),1));
        _label.init();
        //_label << "marseille";
        //_label.setText("molotov");
        
        _scene.addElement(_label.getElement());
        
        
        // Add event listeners
        Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
        
        while (!_close) {
            //Event::Process events
            Event::Manager::getInstance().processEvents();
            // Render
            Graphic::Renderer::getInstance().render();
        }
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            std::cerr << "marseille close" << std::endl;
            _close = true;
        }
    }
    
private:
    bool                _close;
    Graphic::Scene      _scene;
    Widget::Label       _label;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
