//
//  Renderer.cpp
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#include "Renderer.h"

#include "Debug.h"
#include "OpenGL.h"
#include "GraphicException.h"
#include "Event/Manager.h"

static const char* vertexShader =
    "attribute vec3 position;\n"
    "attribute vec2 textureCoords;\n"
    "\n"
    "varying vec2   vTextureCoords;\n"
    "\n"
    "uniform mat4   worldMatrix;\n"
    "uniform mat4   transformationMatrix;\n"
    "\n"
    "void main(){\n"
    "   gl_Position = worldMatrix * transformationMatrix * vec4(position, 1);\n"
    "   vTextureCoords = textureCoords;\n"
    "}\n"
;

static const char* fragmentShader =
# if defined (GRAPHIC_RENDERER_IOS)
    "precision mediump float;\n"
# endif
    "varying vec2       vTextureCoords;\n"
    "uniform sampler2D  textureSampler;\n"
    "void main(){\n"
        "gl_FragColor = texture2D(textureSampler, vec2(vTextureCoords.s, -vTextureCoords.t));\n"
        "gl_FragColor.r = 1.0;\n"
    "}\n"
;

Graphic::Renderer::Settings::Settings(std::string const& title,
                                      Vec2 size,
                                      uint32 antialiasingLevel,
                                      bool fullScreen)
: title(title), size(size), antialiasingLevel(antialiasingLevel), fullScreen(fullScreen) {
}

Graphic::Renderer::Renderer() :
_antialiasingLevel(0), _scene(NULL),
_vertexesBuffer(NULL),
_textureCoordsBuffer(NULL), _indexesBuffer(NULL),
_shaderProgram(NULL),
_vertexPositionLocation(0),
_vertexTextureCoordsLocation(0),
_worldMatrixLocation(0),
_transformationMatrixLocation(0),
_textureSamplerLocation(0) {
}

void Graphic::Renderer::init(Settings const& settings) {
    // Register to the Event manager
    Event::Manager::getInstance().registerProvider(this);
    
    // Let platform-specific code create OpenGL context
    createContext(settings);
    
    // Init and configure OpenGL context
# if !defined OS_IOS
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        throw new Graphic::Exception(std::string("Glew init failed: ")
                                     + reinterpret_cast<const char*>(glewGetErrorString(error)));
    }
# endif
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    
    // Enable blending and antialiasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
# if defined GL_POLYGON_SMOOTH
    if (_antialiasingLevel > 0)
        glEnable(GL_POLYGON_SMOOTH);
# endif
    
    // Background color
    glClearColor(0.f, 0.f, 0.f, 1.f);
    
    // Update the OpenGL viewport (platform-specific)
    updateViewport();
    
    // Create and fill OpenGL Buffers
    _vertexesBuffer = new Bufferf(Bufferf::VertexArray);
    _textureCoordsBuffer = new Bufferf(Bufferf::VertexArray);
    _indexesBuffer = new Bufferui(Bufferui::ElementArray);
    _fillVertexesBuffer();
    _fillTextureCoordsBuffer();
    _fillIndexesBuffer();
    
    // Create the shader
    _shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    _shaderProgram->use();
    
    // Retrieve shader variables locations
    _shaderProgram->registerAttributeLocation("position");
    _vertexPositionLocation = _shaderProgram->getAttributeLocation("position");
    _vertexTextureCoordsLocation = _shaderProgram->getAttributeLocation("textureCoords");
    _worldMatrixLocation = _shaderProgram->getUniformLocation("worldMatrix");
    _transformationMatrixLocation = _shaderProgram->getUniformLocation("transformationMatrix");
    //_shaderProgram->registerUniformLocation("textureSampler");
    //_textureSamplerLocation = _shaderProgram->getUniformLocation("textureSampler");
}

void Graphic::Renderer::destruct() {
    delete _vertexesBuffer;
    delete _textureCoordsBuffer;
    delete _indexesBuffer;
    delete _shaderProgram;
}

void Graphic::Renderer::setScene(Scene const* scene) {
    _scene = scene;
}

void Graphic::Renderer::render(void) {
    if (_scene == NULL)
        throw new Graphic::Exception("Cannot render: No scene specified");
    
    // Clear the framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Enable vertex attributes
    glEnableVertexAttribArray(_vertexPositionLocation);
    glEnableVertexAttribArray(_vertexTextureCoordsLocation);
    
    // Setup data common to all scene elements (world matrix, vertexes, indexes...)
    glUniformMatrix4fv(_worldMatrixLocation, 1, GL_FALSE,
                       (const float32*)_scene->getWorldMatrix());
    
    _vertexesBuffer->bind();
    glVertexAttribPointer(_vertexPositionLocation, 3, GL_FLOAT,
                          GL_FALSE, 0, (void*)0);
    
    _indexesBuffer->bind();
    
    // Draw all scene elements
    std::vector<Element*> const& elements = _scene->getElements();
    
    for (std::vector<Element*>::const_iterator it = elements.begin(),
         end = elements.end(); it != end; ++it) {
        Element* element = *it;
        glUniformMatrix4fv(_transformationMatrixLocation, 1, GL_FALSE,
                           (const float32*)element->getTransformationMatrix());
        
        // Send texture coords for the sprite frame
        element->getSprite()->getTexuteCoordsBuffer()->bind();
        uint32 frameTextureCoordsIndex = element->getCurrentFrame() * 12 * sizeof(GL_FLOAT);
        glVertexAttribPointer(_vertexTextureCoordsLocation, 2, GL_FLOAT,
                              GL_FALSE, 0, (void*)frameTextureCoordsIndex);
        
        // Setup texture
        glActiveTexture(GL_TEXTURE0);
        element->getSprite()->getTexture()->bind();
        glUniform1i(_textureSamplerLocation, 0);

        // Draw element
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glDisableVertexAttribArray(_vertexTextureCoordsLocation);
    glDisableVertexAttribArray(_vertexPositionLocation);
    
    refresh();
}

void Graphic::Renderer::updateViewport(void) {
    Vec2 size = getViewportSize();
    glViewport(0, 0, size.x, size.y);
}

Vec2 Graphic::Renderer::viewportToScene(Vec2 const& coords) const {
    if (_scene == NULL)
        throw new Graphic::Exception("Tried to transform coords but no scene was specified");
    Vec2 viewport = getViewportSize();
    Vec2 scene = _scene->getViewport();
    Vec2 newCoords;
    newCoords.x = coords.x / viewport.x * scene.x;
    newCoords.y = (viewport.y - coords.y) / viewport.y * scene.y;
    return newCoords;
}

Rect2 Graphic::Renderer::viewportToScene(Rect2 const& rect) const {
    if (_scene == NULL)
        throw new Graphic::Exception("Tried to transform coords but no scene was specified");
    Vec2 viewport = getViewportSize();
    Vec2 scene = _scene->getViewport();
    Vec2 newPos = viewportToScene(rect.pos);
    Vec2 newSize = rect.size / viewport * scene;
    newPos.y -= newSize.y;
    Rect2 newRect(newPos, Vec2(newSize));
    return newRect;
}

Vec2 Graphic::Renderer::sceneToViewport(Vec2 const& coords) const {
    if (_scene == NULL)
        throw new Graphic::Exception("Tried to transform coords but no scene was specified");
    Vec2 viewport = getViewportSize();
    Vec2 scene = _scene->getViewport();
    Vec2 newCoords;
    newCoords.x = coords.x / scene.x * viewport.x;
    newCoords.y = (scene.y - coords.y) / scene.y * viewport.y;
    return newCoords;
}

Rect2 Graphic::Renderer::sceneToViewport(Rect2 const& rect) const {
    if (_scene == NULL)
        throw new Graphic::Exception("Tried to transform coords but no scene was specified");
    Vec2 viewport = getViewportSize();
    Vec2 scene = _scene->getViewport();
    Vec2 newPos = sceneToViewport(rect.pos);
    Vec2 newSize = rect.size / scene * viewport;
    newPos.y -= newSize.y;
    Rect2 newRect(newPos, Vec2(newSize));
    return newRect;
}

void Graphic::Renderer::_fillVertexesBuffer(float32 x, float32 y) {
    // Make a rectangle of size 2*x / 2*y , with origin on its center
    static const float32 vertexes[] = {
        // Triangle 1
        -x,     -y, 0.0f,
         x,     -y, 0.0f,
        -x,      y, 0.0f,
        
        // Triangle 2
        -x,     y, 0.0f,
         x,    -y, 0.0f,
         x,     y, 0.0f
    };
    _vertexesBuffer->setData(vertexes, sizeof(vertexes)/sizeof(float32));
}

void Graphic::Renderer::_fillTextureCoordsBuffer(float32 repeatX, float32 repeatY) {
    static const float32 textureCoords[] = {
        0.0f,       0.0f,
        repeatX,    0.0f,
        0.0f,       repeatY,
        
        0.0f,       repeatY,
        repeatX,    0.0f,
        repeatX,    repeatY
    };
    _textureCoordsBuffer->setData(textureCoords, sizeof(textureCoords)/sizeof(float32));
}

void Graphic::Renderer::_fillIndexesBuffer() {
    static const uint32 indexes[] = {
        0, 1, 2, 3, 4, 5
    };
    _indexesBuffer->setData(indexes, sizeof(indexes)/sizeof(uint32));
}