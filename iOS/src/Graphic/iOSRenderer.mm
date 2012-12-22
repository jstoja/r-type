//
//  iOSRenderer.cpp
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#include "Debug.h"
#include "Renderer.h"
#include "Event/Manager.h"
#include "Event/Event.h"

#ifdef GRAPHIC_RENDERER_IOS

# import <UIKit/UIKit.h>
# import <GLKit/GLKit.h>

void Graphic::Renderer::init(GLKView* view) {    
    _context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    if (_context == NULL) {
        throw new Graphic::Exception("Failed to create OpenGL ES context");
    }
    
    _view = view;

    _view.context = _context;
    _view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:_context];
    init();
}

void Graphic::Renderer::createContext(Settings const& settings) {
}

Graphic::Renderer::~Renderer() {
    [_context release];
    destruct();
}

void Graphic::Renderer::processEvents(Event::Manager* manager) {
}

Vec2 Graphic::Renderer::getViewportSize(void) const {
    CGRect  viewRect = _view.bounds;
    CGFloat scale = [[UIScreen mainScreen] scale];
    return Vec2(viewRect.size.width * scale, viewRect.size.height * scale);
}

void Graphic::Renderer::refresh(void) {
}

#endif