//
//  FreetypeFont.cpp
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include <iostream>
#include <string>

#include "FreetypeFont.h"
#include "Exception.h"
#include "ResourcesManager.h"
#include "Resource.h"
#include "Types.h"
#include "Debug.h"

FT_Library  Graphic::FreetypeFont::_library;
bool        Graphic::FreetypeFont::_libraryLoaded = false;

Graphic::FreetypeFont::FreetypeFont(const std::string &resourceName, uint8 size)
: _fontSize(size) {
    
    if (!_libraryLoaded) {
        int error;

        error = FT_Init_FreeType(&_library);
        if (error)
            throw new Exception("An error occurred during Freetype library initialization.");
        _libraryLoaded = true;
    }
    
    loadFont(resourceName);
}

Graphic::FreetypeFont::~FreetypeFont(void) {
    for(unsigned char ch = 0; ch < _characterTab.size(); ++ch) {
        delete[] _characterTab[ch];
    }
    if (_face)
        FT_Done_Face(_face);
}

void Graphic::FreetypeFont::loadFont(const std::string &resourceName) {
    
    Resource* fontResource = ResourcesManager::getInstance().getResource(resourceName);
    
    int error;
    error = FT_New_Memory_Face(_library,
                               (const FT_Byte*)fontResource->getData().getData(),
                               fontResource->getData().getSize(), 0, &_face);
    
    if (error)
		throw new Exception("Cannot load font " + resourceName);
    
    FT_Set_Char_Size(_face, 0, _fontSize * 64, 600, 600);
    
    FT_GlyphSlot slot;
    for (unsigned char ch = 0; ch < 128; ch++) {
        error = FT_Load_Glyph(_face, FT_Get_Char_Index(_face, ch), FT_LOAD_RENDER);
        if (error) {
            throw new Exception("Failed to load glyph from font " + resourceName);
        }
        slot = _face->glyph;
        
        _width.push_back(slot->bitmap.width);
        _height.push_back(slot->bitmap.rows);
        if (ch != ' ')
            _bearingLeft.push_back(slot->bitmap_left);
        else
            _bearingLeft.push_back(slot->advance.x/64);
        _bearingTop.push_back(slot->bitmap_top);
        _characterTab.push_back(_alphaToRGBA(slot->bitmap));
    }
    setColor(255, 255, 255);
}

uint8 *Graphic::FreetypeFont::_alphaToRGBA(FT_Bitmap bitmap) {
    uint8 *data = new uint8[bitmap.width * bitmap.rows * 4];
    
    for (int i = 0; i < bitmap.width * bitmap.rows; ++i) {
        data[i * 4 + 0] = _colorRed;
        data[i * 4 + 1] = _colorGreen;
        data[i * 4 + 2] = _colorBlue;
        data[i * 4 + 3] = bitmap.buffer[i];
    }
    return data;
}

Graphic::Texture *Graphic::FreetypeFont::getStringTexture(std::string &str) {
    Graphic::Texture *tex = new Graphic::Texture();
    
    tex->setData(getStringWidth(str), getStringHeight(str), stringData(str));
    return tex;
}


uint8 *Graphic::FreetypeFont::stringData(std::string const& str) const {
    int maxX = 0;
    int YMax = 0;
    int YMin = 0;
    int esc = 0;
    char c;
    for (int i = 0; i < str.size(); ++i) {
        c = str[i];
        maxX += _width[c];
        if (i != 0) {
            esc += _bearingLeft[c];
        }
        if (_bearingTop[c] > YMax) {
            YMax = _bearingTop[c];
        }
        if ((_height[c] - _bearingTop[c]) > YMin) {
            YMin = _height[c] - _bearingTop[c];
        }
    }

    int maxLineWidth = (maxX + esc) * 4;
    int maxY = YMax + YMin;

    uint8 *data = new uint8[maxLineWidth * maxY];
    memset(data, 0, maxLineWidth * maxY);
    int saveX = 0;
    int lineWidth = 0;
    int debugColor = 0;
    // Iterate over all the chars in the string to add then in the new texture (a RGBA Bitmap)
    for (int ci = 0; ci < str.size(); ++ci) {
        c = str[ci];
        if (ci > 0 && str[ci-1] != ' ') {
            saveX += lineWidth;
            if (_bearingLeft[c] > 0) { //space left between chars
                for (int y = 0; y < maxY; ++y) {
                    memset(data + ((y * maxLineWidth) + saveX), debugColor, _bearingLeft[c] * 4);
                }
                saveX += (_bearingLeft[c] * 4);
            }
        }
        lineWidth = _width[c] * 4;
        // Iterate over all the lines of one char an copy the line in the Texture
        for (int y = 0, YChar = 0; y < maxY; ++y) {
            if (y < (YMax - _bearingTop[c])) { //top of the char
                memset(data + ((y * maxLineWidth) + saveX), debugColor, lineWidth);
            } else if (y < (YMax - _bearingTop[c] + _height[c]) && YChar < _height[c]) { //the char
                memcpy(data + ((y * maxLineWidth) + saveX),
                       _characterTab[c] + ((YChar * lineWidth)),
                       lineWidth);
                ++YChar;
            } else if (y < maxY) { //bottom of the char
                memset(data + ((y * maxLineWidth) + saveX), debugColor, lineWidth);
            }
        }
    }
    return data;
}

int     Graphic::FreetypeFont::getStringWidth(std::string const &str) {
    int save;
    
    save = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (i != 0) {
            save += _width[str[i]] + _bearingLeft[str[i]];
        } else  {
            save += _width[str[i]];
        }
    }
    return save;
}

int     Graphic::FreetypeFont::getStringHeight(std::string const& str) {
    
    int YMax = 0;
    int YMin = 0;
    char c;
    for (int i = 0; i < str.size(); ++i) {
        c = str[i];
        if (_bearingTop[c] > YMax) {
            YMax = _bearingTop[c];
        }
        if ((_height[c] - _bearingTop[c]) > YMin) {
            YMin = _height[c] - _bearingTop[c];
        }
    }
    return YMax + YMin;
}


uint8   *Graphic::FreetypeFont::letterData(char c) const {
    return _characterTab[c];
}

int     Graphic::FreetypeFont::getWidth(char c) const {
    return _width[c];
}

int     Graphic::FreetypeFont::getHeight(char c) const {
    return _height[c];
}

void	Graphic::FreetypeFont::setColor(uint8 r, uint8 g, uint8 b) {
	_colorRed = r;
	_colorGreen = g;
	_colorBlue = b;
}
