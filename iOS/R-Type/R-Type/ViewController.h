//
//  ViewController.h
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

//! Main view controller
/*!
 The view controller is the core of the application, it launch the client
 and act as the interface between all classes and iOS events and user interface
 */
@interface ViewController : GLKViewController

class Client;

@property (nonatomic) Client* client;
@property (strong, nonatomic) EAGLContext *context;

@end
