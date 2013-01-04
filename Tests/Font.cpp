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
#include "Graphic/Font.h"
#include "Graphic/Element.h"
#include "Graphic/Sprite.h"
#include "Graphic/Texture.h"

#include <SFML/Graphics.hpp>

class Test {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
    
		Graphic::FreetypeFont font("/Library/Fonts/marion.ttc", 14);

		std::string str = "nik ta race";
		Graphic::Texture *texture = font.getStringTexture(str);
		
		Graphic::Sprite sprite;
		sprite.setTexture(texture);

		Graphic::Element elem;
		sprite.addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0,  1.0)));
		elem.setSprite(&sprite);
		elem.setCurrentFrame(0);
		elem.setPosition(Vec2(8, 4));
		elem.setSize(Vec2(str.size()-1, 1.0));
        _scene.addElement(&elem);
    	while (!_close) {
            Graphic::Renderer::getInstance().render();
        }
    }
    
    ~Test() {}
    
private:
    bool                _close;
    Graphic::Scene      _scene;
};

int	main(int argc, char *argv[]) {
    try {
        Test client;
        while(1);
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}
