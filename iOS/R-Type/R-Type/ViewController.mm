//
//  ViewController.m
//  R-Type
//
//  Created by Gael du Plessix on 21/12/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
//

#import "ViewController.h"

//@property (strong, nonatomic) EAGLContext *context;
//@property (strong, nonatomic) GLKBaseEffect *effect;
//
//- (void)setupGL;
//- (void)tearDownGL;
//
//- (BOOL)loadShaders;
//- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
//- (BOOL)linkProgram:(GLuint)prog;
//- (BOOL)validateProgram:(GLuint)prog;
//@end

#include "Graphic/Renderer.h"

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    
    
//    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
//
//    if (!self.context) {
//        NSLog(@"Failed to create ES context");
//    }
//    
//    GLKView *view = (GLKView *)self.view;
//    view.context = self.context;
//    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
//    
//    [self setupGL];
}

- (void)dealloc
{    
//    [self tearDownGL];
//    
//    if ([EAGLContext currentContext] == self.context) {
//        [EAGLContext setCurrentContext:nil];
//    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

//    if ([self isViewLoaded] && ([[self view] window] == nil)) {
//        self.view = nil;
//        
//        [self tearDownGL];
//        
//        if ([EAGLContext currentContext] == self.context) {
//            [EAGLContext setCurrentContext:nil];
//        }
//        self.context = nil;
//    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
//    [EAGLContext setCurrentContext:self.context];
//    
//    [self loadShaders];
//    
//    self.effect = [[GLKBaseEffect alloc] init];
//    self.effect.light0.enabled = GL_TRUE;
//    self.effect.light0.diffuseColor = GLKVector4Make(1.0f, 0.4f, 0.4f, 1.0f);
//    
//    glEnable(GL_DEPTH_TEST);
//    
//    glGenVertexArraysOES(1, &_vertexArray);
//    glBindVertexArrayOES(_vertexArray);
//    
//    glGenBuffers(1, &_vertexBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(gCubeVertexData), gCubeVertexData, GL_STATIC_DRAW);
//    
//    glEnableVertexAttribArray(GLKVertexAttribPosition);
//    glVertexAttribPointer(GLKVertexAttribPosition, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(0));
//    glEnableVertexAttribArray(GLKVertexAttribNormal);
//    glVertexAttribPointer(GLKVertexAttribNormal, 3, GL_FLOAT, GL_FALSE, 24, BUFFER_OFFSET(12));
//    
//    glBindVertexArrayOES(0);
}

- (void)tearDownGL
{
//    [EAGLContext setCurrentContext:self.context];
//    
//    glDeleteBuffers(1, &_vertexBuffer);
//    glDeleteVertexArraysOES(1, &_vertexArray);
//    
//    self.effect = nil;
//    
//    if (_program) {
//        glDeleteProgram(_program);
//        _program = 0;
//    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
//    glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    
//    glBindVertexArrayOES(_vertexArray);
//    
//    // Render the object with GLKit
//    [self.effect prepareToDraw];
//    
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    
//    // Render the object again with ES2
//    glUseProgram(_program);
//    
//    glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, _modelViewProjectionMatrix.m);
//    glUniformMatrix3fv(uniforms[UNIFORM_NORMAL_MATRIX], 1, 0, _normalMatrix.m);
//    
//    glDrawArrays(GL_TRIANGLES, 0, 36);
}

@end
