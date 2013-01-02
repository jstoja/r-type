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
    
		Graphic::FreetypeFont font("/Library/Fonts/Marion.ttc", 14);

		Graphic::Texture texture;
		//texture.setData(font.getWidth('b'), font.getHeight('b'), font.letterData('b'));
		
		//std::string str("a");
		//texture.setData(font.getWidth('a'), font.getHeight('a'), font.stringData(str));
		
		std::string str("a bd");
		std::cout << font.getStringWidth(str) << std::endl;
		std::cout << font.getStringHeight(str) << std::endl;
		texture.setData(font.getStringWidth(str), font.getStringHeight(str), font.stringData(str));
		
		Graphic::Sprite sprite;
		sprite.setTexture(&texture);

		Graphic::Element elem;
		sprite.addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0), Vec2(1.0,  1.0)));
		elem.setSprite(&sprite);
		elem.setCurrentFrame(0);
		elem.setPosition(Vec2(8, 4));
		elem.setSize(Vec2(1, 1));
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
