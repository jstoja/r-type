//
//  Image.cpp
//  R-Type
//
//  Created by Gael du Plessix on 11/01/13.
//
//

#include "Image.h"
#include "ResourcesManager.h"
#include "Resource.h"
#include "Debug.h"

Graphic::Image::Image(std::string const& resourceName, bool generateId)
: _pixels(NULL), _width(0), _height(0) {
    if (!resourceName.empty())
        loadFromResource(resourceName, generateId);
}

Graphic::Image::~Image() {
    if (_pixels)
        delete[] _pixels;
}

void Graphic::Image::loadFromResource(std::string const& resourceName, bool generateId) {
    Resource* resource = ResourcesManager::getInstance().getResource(resourceName, generateId);
    
    loadFromData(resource->getData());
}

uint8 const* Graphic::Image::getPixelsPtr() const {
    return _pixels;
}

uint32 Graphic::Image::getWidth(void) const {
    return _width;
}

uint32 Graphic::Image::getHeight(void) const {
    return _height;
}

Vec2 Graphic::Image::getSize(void) const {
    return Vec2(_width, _height);
}