#include <iostream>
#include <string>

#include <Exception.h>
#include <Application.h>
#include "Types.h"
#include "Font.h"

Graphic::FreetypeFont::FreetypeFont(uint8 size, const std::string &path)
: _fontLoaded(false), _fontPath(path), _fontSize(size) {
	if (_fontPath.empty()) {
		_fontPath = Application::getInstance().getResourcesPath() + "./Marion.ttc";
	}
    int         error;

    error = FT_Init_FreeType(&_library);
    if (error)
        throw new Exception("An error occurred during Freetype library initialization.");
    changeFont(_fontPath, _fontSize);
}

void Graphic::FreetypeFont::changeFont(const std::string &fontPath, uint8 size) {
    _fontLoaded = false;
    _fontSize = size;
    _fontPath = fontPath;
    
    int         error;
    error = FT_New_Face(_library, fontPath.c_str(), 0, &_face);
    if ( error == FT_Err_Unknown_File_Format )
        throw new Exception("The font file could be opened and read, but it appears that its font format is unsupported.");
    else if (error)
		throw new Exception("The font file \"" + fontPath + "\"could not be opened or read, or simply that it is broken.");
    FT_Set_Char_Size(_face, 0, size * 64, 600, 600);
    
    FT_GlyphSlot slot;
    for (unsigned char ch = 0; ch < 128; ch++) {
        error = FT_Load_Glyph(_face, FT_Get_Char_Index(_face, ch), FT_LOAD_RENDER);
        if (error) {
            throw new Exception("FT_Load_Glyph failed");
        }
        slot = _face->glyph;
        
        _width.push_back(slot->bitmap.width);
        _height.push_back(slot->bitmap.rows);
        if (ch != ' ')
            _bearingLeft.push_back(slot->bitmap_left);
        else
            _bearingLeft.push_back(slot->advance.x/64);
        _bearingTop.push_back(slot->bitmap_top);
        _characterTab.push_back(_returnRGBA(slot->bitmap.buffer, slot->bitmap.width * slot->bitmap.rows * 4));
    }
    _fontLoaded = true;
}

Graphic::FreetypeFont::~FreetypeFont(void) {
    if (_fontLoaded == true) {
        for(unsigned char ch = 0; ch < _characterTab.size(); ++ch) {
            delete[] _characterTab[ch];
        }
        FT_Done_Face(_face);
    }
    FT_Done_FreeType(_library);
}


uint8 *Graphic::FreetypeFont::_returnRGBA(uint8* bitmap, int size) {
    uint8 *data = new uint8[size];
    int i, j;
    
    for (i = 0, j = 0; i < size; i += 4, j++) {
        if (bitmap[j] != 0) {
            data[i] = 255;
            data[i+1] = 255;
            data[i+2] = 255;
            data[i+3] = bitmap[j];
        } else {
            data[i] = 0;
            data[i+1] = 0;
            data[i+2] = 0;
            data[i+3] = bitmap[j];
        }
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
    int YChar = 0;
    int saveX = 0;
    int lineWidth = 0;
    int debugColor = 0;
    // Iterate over all the chars in the string to add then in the new texture (a RGBA Bitmap)
    for (int ci = 0; ci < str.size(); ++ci) {
        c = str[ci];
        if (ci > 0 && str[ci-1] != ' ') {
            saveX += lineWidth;
            if (_bearingLeft[c] > 0) {//space left between chars
                for (int y = 0; y < maxY; ++y) {
                    memset(data + ((y * maxLineWidth) + saveX), debugColor, _bearingLeft[c] * 4);
                }
                saveX += (_bearingLeft[c] * 4);
            }
        }
        lineWidth = _width[c] * 4;
        // Iterate over all the lines of one char an copy the line in the Texture
        for (int y = 0, YChar = 0; y < maxY; ++y) {
            if (y < (YMax - _bearingTop[c])) {//top of the char
                memset(data + ((y * maxLineWidth) + saveX), debugColor, lineWidth);
            } else if (y < (YMax - _bearingTop[c] + _height[c]) && YChar < _height[c]) { //the char
                memcpy(data + ((y * maxLineWidth) + saveX),
                       _characterTab[c] + ((YChar * lineWidth)),
                       lineWidth);
                ++YChar;
            } else if (y < maxY) {//bottom of the char
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
