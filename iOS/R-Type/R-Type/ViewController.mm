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

#include "Debug.h"
#include "Event/Manager.h"
#include "Event/IListenerDelegate.h"
#include "Graphic/Renderer.h"
#include "Graphic/Scene.h"

class Test : public Event::IListenerDelegate {
public:
    Test(GLKView* view)
    : _close(false), _scene(), _button() {
        
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
        //buttonTexture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
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
        Graphic::Renderer::getInstance().render();
    }
    
    ~Test() {}
    
    virtual void processEvent(Event::Event const& event) {
        if (event.type == Event::Close) {
            _close = true;
        } else if (event.type & Event::PointerIn) {
            _button.setCurrentFrame(2);
        } else if (event.type & Event::PointerOut) {
            _button.setCurrentFrame(0);
        } else if (event.type & Event::PointerPushed) {
            _button.setCurrentFrame(1);
        } else if (event.type & Event::PointerReleased) {
            _button.setCurrentFrame(2);
        }
    }
    
private:
    bool                _close;
    Graphic::Scene      _scene;
    Graphic::Element    _button;
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
    [super dealloc];
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
    _test->render();
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
