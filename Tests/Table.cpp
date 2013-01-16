//
// Table.cpp
// R-Type
//
// Created by Franck Lavisse on 10/01/13.
//
//
#include <SFML/Graphics.hpp>

#include <Application.h>

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Widget/Widget.h"
#include "Widget/GraphicWidget.h"
#include "Widget/Button.h"
#include "Widget/CheckBox.h"
#include "Widget/Label.h"
#include "Widget/Table.h"
#include "Widget/ITableDelegate.h"

class Test : public Event::IListenerDelegate, public Widget::ITableDelegate {
public:
    Test()
    : _close(false), _scene() {
        
        // Setup renderer
        Graphic::Renderer::getInstance().init();
        Graphic::Renderer::getInstance().setScene(&_scene);

		_table = new Widget::Table(2, "table-lines.png", &_scene, this);
		_table->setPosition(Vec3(8, 4.5));
		_table->setHeaderName("C1", 0);
		_table->setHeaderName("C2", 1);
		_table->setLineNumberByPage(8);
		_table->setColumnAlignement(Widget::Table::Right, 1);
		std::vector<std::string>	data;
		data.push_back("V1/1");
		data.push_back("V1/2");
		_table->addLine(data);
		data.clear();
		data.push_back("V2/1");
		data.push_back("V2/2");
		_table->addLine(data);
		//data.clear();
		//data.push_back("V3/1");
		//data.push_back("V3/2");
		//_table->addLine(data);
		//data.clear();
		//data.push_back("V4/1");
		//data.push_back("V4/2");
		//_table->addLine(data);
		//data.clear();
		//data.push_back("V5/1");
		//data.push_back("V5/2");
		//_table->addLine(data);
		//data.clear();
		//data.push_back("V6/1");
		//data.push_back("V6/2");
		//_table->addLine(data);
		_table->setColor(1, Vec3(1, 0, 0));
		// Add event listeners
		Event::Manager::getInstance().addEventListener(new Event::Listener(Event::Close, this));
        while (!_close) {
            // Process events
            Event::Manager::getInstance().processEvents();
            
            // Render
            Graphic::Renderer::getInstance().render();
        }
    }
    
	void	linePushed(Widget::Table* table, uint32 line) {
		std::cout << "Pushed line: " << line << std::endl;
		_table->nextPage();
	}

    ~Test() {
		delete _table;	
	}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        }
    }
    
private:
    Widget::Table       *_table;
    bool                _close;
    Graphic::Scene      _scene;
};

int	main(int argc, char *argv[]) {
    try {
		App.init(argc, argv);
		App.setRelativeResourcesPath("../Client/Resources/");
        Test client;
    } catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
	return (0);
}

