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

Graphic::Texture::Texture() : Object(false), _glID(0), _size(0) {
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


Graphic::Texture::Texture(uint32 id, Resource* resource) : Object(id), _glID(0), _size(0) {
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Graphic::Image image;
	image.loadFromData(resource->getData());
    setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
}

Graphic::Texture::Texture(const std::string& resourceImage, bool generateId)
: Object(false), _glID(0), _size(0) {
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    Graphic::Image image;
    image.loadFromResource(resourceImage, generateId);
    setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
}

Graphic::Texture::~Texture() {
    glDeleteTextures(1, &_glID);
}

void Graphic::Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _glID);
}


void Graphic::Texture::setData(uint32 width, uint32 height, const uint8* data) {
    bind();
    glTexImage2D(GL_TEXTURE_2D,     // Texture type
                 0,                 // Level of detail (0 = max)
                 GL_RGBA,           // Internal format
                 width,             // Width
                 height,            // Height
                 0,                 // This value must be 0
                 GL_RGBA,           // Format of the pixel datas
                 GL_UNSIGNED_BYTE,  // Data type of the pixel datas
                 data);
    Graphic::Exception::checkOpenGLError();
    _size.x = width;
    _size.y = height;
}

uint32 Graphic::Texture::getGLID(void) const {
    return _glID;
}

Vec2 const& Graphic::Texture::getSize(void) const {
    return _size;
}