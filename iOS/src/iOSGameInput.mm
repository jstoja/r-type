//
//  iOSGameInput.mm
//  R-Type
//
//  Created by Gael du Plessix on 20/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "OS.h"

#ifdef OS_IOS

# include "GameInput.h"
# include "iOSMainViewController.h"

GameInput::GameInput() {
}

GameInput::~GameInput() {
}

void GameInput::enable(void) {
    [iOSMainViewController::getInstance().getViewController() enableGameInput];
}

void GameInput::disable(void) {
    [iOSMainViewController::getInstance().getViewController() disableGameInput];
}

#endif