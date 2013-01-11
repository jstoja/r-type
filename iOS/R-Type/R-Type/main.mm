//
//  main.m
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AppDelegate.h"

#include "Debug.h"
#include "Exception.h"
#include <exception>

#include "Application.h"

int main(int argc, char *argv[])
{
    Application::getInstance().init(argc, argv);
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}
