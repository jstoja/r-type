#include "Debug.h"
#include "Event/Manager.h"
#include "Event/Listener.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"
#include "Widgets/Widget.h"
#include "Widgets/GraphicWidget.h"
#include "Menu/LoginMenu.h"
#include "Menu/IMenuDelegate.h"
#include "Application.h"

class Test : public Event::IListenerDelegate,
             public Menu::IMenuDelegate {
public:
    Test()
    : _close(false), _scene(), _button() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        Menu::LoginMenu lmenu(&_scene, this);
        
        // Add event listeners
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            // Render
            Graphic::Renderer::getInstance().render();
            //usleep(10000);
        }
    }
    
    ~Test() {}
    virtual void welcomeCompleted() {}

    virtual void loginCompleted(std::string const& login, std::string const& ipAddress, std::string const& port) {
		std::cout << "Connection from " << login << " to " << ipAddress << " " << port << std::endl;
        _close = true;
    }
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        }
    }

    virtual void newGameCallGeneralMenu() {}
    virtual void serverListCallGeneralMenu() {}
    virtual void optionsCallGeneralMenu() {}

private:
    bool                _close;
    Graphic::Scene      _scene;
    Graphic::Element    _button;
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
