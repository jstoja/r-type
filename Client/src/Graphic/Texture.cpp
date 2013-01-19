//
//  Texture.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include "Texture.h"

#include "Debug.h"
#include "UUIDGenerator.h"
#include "GraphicException.h"
#include "Graphic/TextureManager.h"

Graphic::Texture::Texture() :
Object(false), _isInit(false), _dataToLoad(NULL), _glID(0), _size(0) {
    Graphic::TextureManager::getInstance().registerTexture(this);
}


Graphic::Texture::Texture(uint32 id, Resource* resource) :
Object(id), _isInit(false), _dataToLoad(NULL), _glID(0), _size(0) {
	Graphic::Image image;
	image.loadFromData(resource->getData());
    setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
    
    Graphic::TextureManager::getInstance().registerTexture(this);
}

Graphic::Texture::Texture(const std::string& resourceImage, bool generateId) :
Object(false), _isInit(false), _dataToLoad(NULL), _glID(0), _size(0) {
    Graphic::Image image;
    image.loadFromResource(resourceImage, generateId);
    setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
    
    Graphic::TextureManager::getInstance().registerTexture(this);
}

Graphic::Texture::~Texture() {
    if (_isInit)
        glDeleteTextures(1, &_glID);
    Graphic::TextureManager::getInstance().unregisterTexture(this);
}

void Graphic::Texture::init(void) {
    // If we don't have data to load, we can't init the texture
    if (!_dataToLoad)
        return ;
    
    _isInit = true;
    
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Send the data to the texture
    glTexImage2D(GL_TEXTURE_2D,     // Texture type
                 0,                 // Level of detail (0 = max)
                 GL_RGBA,           // Internal format
                 _size.x,           // Width
                 _size.y,           // Height
                 0,                 // This value must be 0
                 GL_RGBA,           // Format of the pixel datas
                 GL_UNSIGNED_BYTE,  // Data type of the pixel datas
                 _dataToLoad);
    Graphic::Exception::checkOpenGLError();
    
    delete[] _dataToLoad;
    _dataToLoad = NULL;
}

bool Graphic::Texture::isInit(void) const {
    return _isInit;
}

void Graphic::Texture::bind() {
    if (!_isInit)
        return ;
    glBindTexture(GL_TEXTURE_2D, _glID);
}


void Graphic::Texture::setData(uint32 width, uint32 height, const uint8* data) {
    // Save the data that will be loaded later
    _size.x = width;
    _size.y = height;
    _dataToLoad = new uint8[width * height * 4];
    memcpy((void*)_dataToLoad, data, width * height * 4);
}

uint32 Graphic::Texture::getGLID(void) const {    
    return _glID;
}

Vec2 const& Graphic::Texture::getSize(void) const {
    return _size;
}