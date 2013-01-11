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

Graphic::Texture::Texture() : Object(), _glID(0) {
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


Graphic::Texture::Texture(uint32 id) : Object(id), _glID(0) {
    glGenTextures(1, &_glID);
    
    // Configure the texture
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
}

void Graphic::Texture::setDataFromFile(std::string const& fileName) {
    uint32        width;
    uint32        height;
    const uint8   *data;

    #ifndef OS_IOS
        sf::Image image;
        image.loadFromFile(fileName.c_str());
        width = image.getSize().x;
        height = image.getSize().y;
        data = image.getPixelsPtr();
    #endif
    #ifdef OS_IOS
    #endif
    
    setData(width, height, data);
}

uint32 Graphic::Texture::getGLID() const {
    return _glID;
}
