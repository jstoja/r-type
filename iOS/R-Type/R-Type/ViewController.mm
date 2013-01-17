//
//  ViewController.m
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import "ViewController.h"

#include <exception>
#include "iOSMainViewController.h"
#include "Client.h"
#include "Graphic/Renderer.h"
#include "Debug.h"
#include "Widget/TextEdit.h"

@implementation ViewController

//! Entry point of the application
- (void)viewDidLoad
{
    [super viewDidLoad];

    try {
        iOSMainViewController::getInstance().setViewController(self);
        self.client = new Client();
    }
    catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
}

-(void)openTextInput {    
    [self performSegueWithIdentifier:@"TextInputController" sender:self];
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerPushed,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        event.pointerButton = Event::PointerLeft;
        iOSMainViewController::getInstance().pushEvent(event);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerMove,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        event.pointerButton = Event::PointerLeft;
        iOSMainViewController::getInstance().pushEvent(event);
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        CGPoint location = [touchEvent locationInView:self.view];
        Event::Event event(Event::PointerReleased,
                           Graphic::Renderer::getInstance()
                           .viewportToScene(Vec2(location.x, location.y)));
        event.pointerButton = Event::PointerLeft;        
        iOSMainViewController::getInstance().pushEvent(event);
    }
}

- (void)dealloc
{
    delete self.client;
    
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

- (void)update
{
    try {
        _client->update();
    }
    catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    try {
        _client->render();
    }
    catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
}

@end
