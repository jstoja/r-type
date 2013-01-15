//
//  iOSApplication.mm
//  R-Type
//
//  Created by Gael du Plessix on 11/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "OS.h"
#include "Application.h"

# if defined OS_IOS

void Application::_initBinaryPath(void) {
    _binaryPath = new std::string([[[NSBundle mainBundle] resourcePath] UTF8String]);
}

# endif
