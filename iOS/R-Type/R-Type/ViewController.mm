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
#include "GameInput.h"

static CGPoint defaultJoystickPosition;

@implementation ViewController

//! Entry point of the application
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    defaultJoystickPosition = self.joystickBackground.center;
    [self disableGameInput];

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

-(void)disableGameInput {
    [self hideJoystick];
    self.joystickTouch = nil;
    self.joystickBackground.hidden = YES;
    self.joystickButton.hidden = YES;
    self.shootButton.hidden = YES;
    self.gameInputEnabled = NO;
}

-(void)enableGameInput {
    self.gameInputEnabled = YES;
    self.joystickTouch = nil;
    self.joystickButton.center = defaultJoystickPosition;
    self.joystickBackground.center = defaultJoystickPosition;
    self.joystickBackground.hidden = NO;
    self.joystickButton.hidden = NO;
    self.shootButton.hidden = NO;
    [self hideJoystick];
}

-(void)hideJoystick {
    if (self.gameInputEnabled) {
        [UIView animateWithDuration:0.2 animations:^{
            self.joystickBackground.alpha = 0.4;
            self.joystickButton.alpha = 0.4;
            self.joystickButton.center = self.joystickBackground.center;
        }];
        _joystickValue = Vec2(0.0, 0.0);
        GameInput::getInstance().setInputDirection(_joystickValue * Vec2(1, -1));
    }
}

-(void)showJoystick {
    if (self.gameInputEnabled) {
        self.joystickBackground.alpha = 1.0;
        self.joystickButton.alpha = 1.0;
        self.joystickBackground.center = [self.joystickTouch locationInView:self.view];
        self.joystickButton.center = [self.joystickTouch locationInView:self.view];
        _joystickValue = Vec2(0.0, 0.0);
        GameInput::getInstance().setInputDirection(_joystickValue * Vec2(1, -1));
    }
}

-(void)updateJoystick {
    if (self.gameInputEnabled) {
        self.joystickButton.center = [self.joystickTouch locationInView:self.view];
        Vec2 buttonPos(self.joystickButton.center.x, self.joystickButton.center.y);
        Vec2 center(self.joystickBackground.center.x, self.joystickBackground.center.y);
        _joystickValue = buttonPos - center;
        if (_joystickValue.norm() > self.joystickBackground.frame.size.width / 2) {
            _joystickValue.normalize();
            Vec2 newPos = center + _joystickValue * self.joystickBackground.frame.size.width / 2;
            self.joystickButton.center = CGPointMake(newPos.x, newPos.y);
        } else
            _joystickValue = _joystickValue / (self.joystickBackground.frame.size.width / 2);
        GameInput::getInstance().setInputDirection(_joystickValue * Vec2(1, -1));
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch* touchEvent in touches) {
        if (self.gameInputEnabled && self.joystickTouch == nil) {
            self.joystickTouch = touchEvent;
            [self showJoystick];
        }
        
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
        if (self.gameInputEnabled && touchEvent == self.joystickTouch) {
            [self updateJoystick];
        }
        
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
        if (self.gameInputEnabled && touchEvent == self.joystickTouch) {
            self.joystickTouch = nil;
            [self hideJoystick];
        }
        
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
    
    [_shootButton release];
    [_joystickBackground release];
    [_joystickButton release];
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
