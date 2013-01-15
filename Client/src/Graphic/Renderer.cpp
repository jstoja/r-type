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

#ifndef OS_IOS
template <> Graphic::Renderer* Singleton<Graphic::Renderer>::_instance = new Graphic::Renderer();
#endif

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
    "\n"
    "uniform sampler2D  textureSampler;\n"
    "uniform float      opacity;\n"
    "void main(){\n"
        "gl_FragColor = texture2D(textureSampler, vec2(vTextureCoords.s, -vTextureCoords.t));\n"
        "gl_FragColor.a *= opacity;\n"
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
    // Fill the texture coords buffer, used to draw sceneries
    _fillTextureCoordsBuffer(2, 1);
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
    _textureSamplerLocation = _shaderProgram->getUniformLocation("textureSampler");
    _opacityLocation = _shaderProgram->getUniformLocation("opacity");
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
    
    // Setup data used by every scene components (vertexes, indexes...)
    _vertexesBuffer->bind();
    glVertexAttribPointer(_vertexPositionLocation, 3, GL_FLOAT,
                          GL_FALSE, 0, (void*)0);
    _indexesBuffer->bind();
    
    // Start by drawing background components
    _renderSceneries();
    
    // Setup data common to all scene elements (world matrix...)
    glUniformMatrix4fv(_worldMatrixLocation, 1, GL_FALSE,
                       (const float32*)_scene->getViewportMatrix());
    
    // Draw static and dynamic scene elements
    std::vector<Element*> const& elements = _scene->getElements();
    
    for (std::vector<Element*>::const_iterator it = elements.begin(),
         end = elements.end(); it != end; ++it) {
        Element* element = *it;
        if (!element->isVisible() || !(element->getType() == Element::Static
              || element->getType() == Element::Dynamic))
            continue;
        // Set element transformation matrix
        glUniformMatrix4fv(_transformationMatrixLocation, 1, GL_FALSE,
                           (const float32*)element->getTransformationMatrix());
        // And opacity
        glUniform1f(_opacityLocation, element->getOpacity());
        
        _setupElementTexture(element);

        // Draw element
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    // Draw floating elements
    glUniformMatrix4fv(_worldMatrixLocation, 1, GL_FALSE,
                       (const float32*)_scene->getWorldMatrix());
    
    for (std::vector<Element*>::const_iterator it = elements.begin(),
         end = elements.end(); it != end; ++it) {
        Element* element = *it;
        if (!element->isVisible() || !(element->getType() == Element::Floating))
            continue;
        // Set element transformation matrix
        glUniformMatrix4fv(_transformationMatrixLocation, 1, GL_FALSE,
                           (const float32*)element->getTransformationMatrix());
        // And opacity
        glUniform1f(_opacityLocation, element->getOpacity());
        
        _setupElementTexture(element);
        
        // Draw element
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    glDisableVertexAttribArray(_vertexTextureCoordsLocation);
    glDisableVertexAttribArray(_vertexPositionLocation);
    
    refresh();
}

void Graphic::Renderer::_renderSceneries(void) {
    // Setup the world matrix and texture coords, common to all sceneries
    glUniformMatrix4fv(_worldMatrixLocation, 1, GL_FALSE,
                       (const float32*)_scene->getWorldMatrix());
    _textureCoordsBuffer->bind();
    glVertexAttribPointer(_vertexTextureCoordsLocation, 2, GL_FLOAT,
                          GL_FALSE, 0, (void*)0);

    std::vector<Graphic::Scenery*> const& sceneries = _scene->getSceneries();
    for (std::vector<Graphic::Scenery*>::const_iterator it = sceneries.begin(),
         end = sceneries.end(); it != end; ++it) {
        if ((*it)->getRange().x <= _scene->getViewportPosition().x
            && (*it)->getRange().y >= _scene->getViewportPosition().x)
            _renderScenery(*it);
    }
}

void Graphic::Renderer::_renderScenery(Scenery* scenery) {
    // Get the x position of the scenery, relative to time
    float sceneryWidth = scenery->getWidth();
    float xPos = _scene->getViewportPosition().x * scenery->getSpeed() / sceneryWidth;
    xPos = xPos - (int)xPos;
    xPos = sceneryWidth * (1 - xPos);

    // Create the scenery rect with a transformation matrix
    Matrix4f transformationMatrix;
    transformationMatrix.translate(xPos, 4.5, 0);
    transformationMatrix.scale(sceneryWidth * 2,
                               _scene->getViewport().y);
    transformationMatrix.translate(0, 0, scenery->getDepth());
    // Send it to the GPU
    glUniformMatrix4fv(_transformationMatrixLocation, 1, GL_FALSE,
                       (const float32*)transformationMatrix);
    
    // Set the scenery opacity
    glUniform1f(_opacityLocation, scenery->getOpacity());
    
    glActiveTexture(GL_TEXTURE0);
    scenery->getTexture()->bind();
    glUniform1i(_textureSamplerLocation, 0);
    
    // Draw the scenery
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Graphic::Renderer::_setupElementTexture(Element* element) {
    // Send texture coords for the sprite frame
    if (!element->getSprite())
        throw new Graphic::Exception("Trying to render an element with no sprite");
    if (!element->getSprite()->getTexture())
        throw new Graphic::Exception("Trying to render an element with no texture");
    element->getSprite()->getTexuteCoordsBuffer()->bind();
    uint32 frameTextureCoordsIndex = element->getCurrentFrame() * 12 * sizeof(GL_FLOAT);
    glVertexAttribPointer(_vertexTextureCoordsLocation, 2, GL_FLOAT,
                          GL_FALSE, 0, (void*)frameTextureCoordsIndex);
    
    // Setup texture
    glActiveTexture(GL_TEXTURE0);
    element->getSprite()->getTexture()->bind();
    glUniform1i(_textureSamplerLocation, 0);
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

void Graphic::Renderer::_fillVertexesBuffer(float32 x, float32 y, float32 z) {
    // Make a rectangle of size 2*x / 2*y , with origin on its center
    float32 vertexes[] = {
        // Triangle 1
        -x,     -y, z,
         x,     -y, z,
        -x,      y, z,
        
        // Triangle 2
        -x,     y, z,
         x,    -y, z,
         x,     y, z
    };
    _vertexesBuffer->setData(vertexes, sizeof(vertexes)/sizeof(float32));
}

void Graphic::Renderer::_fillTextureCoordsBuffer(float32 repeatX, float32 repeatY) {
    float32 textureCoords[] = {
        0.0f,       0.0f,
        repeatX,    0.0f,
        0.0f,       repeatY,
        
        0.0f,       repeatY,
        repeatX,    0.0f,
        repeatX,    repeatY
    };
    static bool update = false;
    if (!update) {
        _textureCoordsBuffer->setData(textureCoords, sizeof(textureCoords)/sizeof(float32));
        update = true;
    } else
        _textureCoordsBuffer->setData(textureCoords, 0, sizeof(textureCoords)/sizeof(float32));
}

void Graphic::Renderer::_fillIndexesBuffer() {
    uint32 indexes[] = {
        0, 1, 2, 3, 4, 5
    };
    _indexesBuffer->setData(indexes, sizeof(indexes)/sizeof(uint32));
}