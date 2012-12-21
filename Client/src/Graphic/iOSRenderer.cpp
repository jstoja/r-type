//
//  iOSRenderer.cpp
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#include "Debug.h"
#include "Renderer.h"
#include "Manager.h"
#include "Event.h"

#ifdef GRAPHIC_RENDERER_IOS

void Graphic::Renderer::createContext(Settings const& settings) {
}

Graphic::Renderer::~Renderer() {
    destruct();
}

void Graphic::Renderer::processEvents(Event::Manager* manager) {
}

Vec2 Graphic::Renderer::getViewportSize(void) const {
    return Vec2();
}

void Graphic::Renderer::refresh(void) {
}

#endif