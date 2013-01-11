//
//  SfmlImage.cpp
//  R-Type
//
//  Created by Gael du Plessix on 11/01/13.
//
//

#ifndef OS_IOS

# include "Graphic/Image.h"
# include "Graphic/GraphicException.h"
# include <SFML/Graphics/Image.hpp>

void Graphic::Image::loadFromData(ByteArray const& data) {
    sf::Image image;
    
    if (!image.loadFromMemory((void*)data.getData(), data.getSize())) {
        throw new Graphic::Exception("Cannot load image from data");
    }
    _width = image.getSize().x;
    _height = image.getSize().y;
    uint32 dataSize = _width * _height * 4;
    if (_pixels)
        delete _pixels;
    _pixels = new uint8[dataSize];
    memcpy((void*)_pixels, image.getPixelsPtr(), dataSize);
}

#endif