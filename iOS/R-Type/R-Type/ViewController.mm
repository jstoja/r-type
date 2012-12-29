//
//  ViewController.m
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import "ViewController.h"

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"

#include <stack>

class Test : public Event::IListenerDelegate, public Event::IProvider {
public:
    Test(GLKView* view)
    : _close(false), _scene(), _button() {
        
        
        // Register this class as an event provider, so it can pass events
        // from the view controller to the event manager
        Event::Manager::getInstance().registerProvider(this);
        
        // Setup renderer
        Graphic::Renderer::getInstance().init(view);
        Graphic::Renderer::getInstance().setScene(&_scene);
        
        // Setup scene
        _button.setPosition(Vec2(8, 4.5));
        _button.setSize(Vec2(9, 3));
        
        //        Graphic::Element* button2 = new Graphic::Element();
        //        button2->setPosition(Vec2(2, 2));
        //        button2->setSize(Vec2(3, 1));
        
//        sf::Image image;
//        image.loadFromFile("button.png");
        
        Graphic::Texture* buttonTexture = new Graphic::Texture();
        
        NSString* imagePath = [[[NSBundle mainBundle] URLForResource:@"button" withExtension:@"png"] path];
        UIImage* image = [[UIImage alloc] initWithContentsOfFile:imagePath];
        if (image) {
            uint8* imageData = getImageData(image);
            if (imageData) {
                buttonTexture->setData(image.size.width,
                                       image.size.height,
                                       imageData);     
                free(imageData);
            }
            [image release];
        }

        Graphic::Sprite* buttonSprite = new Graphic::Sprite();
        buttonSprite->setTexture(buttonTexture);
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.0),      Vec2(1.0,  0.333333)));
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.333333), Vec2(1.0, 0.666666)));
        buttonSprite->addFrame(Graphic::Sprite::Frame(Vec2(0.0, 0.666666), Vec2(1.0, 1)));
        
        _button.setSprite(buttonSprite);
        _button.setCurrentFrame(0);
        
        //        button2->setSprite(buttonSprite);
        //        _scene.addElement(button2);
        
        _scene.addElement(&_button);
        
        // Add event listeners
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::Close, this));
        Event::Manager::getInstance()
        .addEventListener(new Event::Listener(Event::PointerIn
                                              | Event::PointerOut
                                              | Event::PointerMove
                                              | Event::PointerPushed
                                              | Event::PointerReleased,
                                              _button.getRect(),
                                              this));
        
//        while (!_close) {
//            // Process events
//            Event::Manager::getInstance().processEvents();
//
//            // Render
//            _renderer.render();
//        }
    }
    
    void render() {
        Event::Manager::getInstance().processEvents();
        Graphic::Renderer::getInstance().render();
    }
    
    ~Test() {}
    
    uint8* getImageData(UIImage* image) {
        CGImageRef imageRef = [image CGImage];
        
        NSUInteger width = CGImageGetWidth(imageRef);
        NSUInteger height = CGImageGetHeight(imageRef);
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        uint8* rawData = (uint8*)malloc(height * width * 4);
        NSUInteger bytesPerPixel = 4;
        NSUInteger bytesPerRow = bytesPerPixel * width;
        NSUInteger bitsPerComponent = 8;
        CGContextRef context = CGBitmapContextCreate(rawData, width, height,
                                                     bitsPerComponent, bytesPerRow, colorSpace,
                                                     kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
        CGContextRelease(context);
        
        return rawData;
    }
    
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
