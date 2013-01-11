//
//  ViewController.m
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import "ViewController.h"

#include "Application.h"
#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"
#include "Graphic/Image.h"

#include <stack>

class Test : public Event::IListenerDelegate, public Event::IProvider {
public:
    Test(GLKView* view)
    : _close(false), _scene(), _button(), _xPos(0) {
        
        // Register this class as an event provider, so it can pass events
        // from the view controller to the event manager
        Event::Manager::getInstance().registerProvider(this);
        
        // Setup renderer
        Graphic::Renderer::getInstance().init(view);
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        // Adjust the scene size to device format
        Vec2 viewport = _scene.getViewport();
        Vec2 screen = Graphic::Renderer::getInstance().getViewportSize();
        viewport.x = viewport.y * screen.y / screen.x;
        _scene.setViewport(viewport);
        
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
        scenery->setOpacity(0.33);
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

    }
    
    void render() {
        Event::Manager::getInstance().processEvents();
        Graphic::Renderer::getInstance().render();
        
        _scene.setViewportPosition(Vec2(_xPos, 0));
        
        _xPos += 0.1;
    }
    
    ~Test() {}
        
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        } else if (event.type & Event::PointerOut) {
            _button.setCurrentFrame(0);
        } else if (event.type & Event::PointerPushed) {
            _button.setCurrentFrame(1);
        } else if (event.type & Event::PointerReleased) {
            _button.setCurrentFrame(0);
        }
    }
    
    virtual void processEvents(Event::Manager* manager) {
        while (!_events.empty()) {
            manager->fire(_events.top());
            _events.pop();
        }
    }
    
    void pushEvent(Event::Event& event) {
        event.sender = this;
        _events.push(event);
    }
    
    
private:
    bool                        _close;
    Graphic::Scene              _scene;
    Graphic::Element            _button;
    std::stack<Event::Event>    _events;
    float                       _xPos;    
};


@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    try {
        _test = new Test((GLKView *)self.view);
    } catch (Exception* e) {
        Log("Error: " << e->getMessage());
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerPushed,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        _test->pushEvent(event);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerMove,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        _test->pushEvent(event);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerReleased,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        _test->pushEvent(event);
    }
}

- (void)dealloc
{    
    [super dealloc];
}

-(NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskLandscape;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    _test->render();
}

@end
