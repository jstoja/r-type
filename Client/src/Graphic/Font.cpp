#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H
//#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
//#include <freetype/ftoutln.h>
//#include <freetype/fttrigon.h>

#include "Types.h"
#include "Font.h"

Graphic::FreetypeFont::FreetypeFont(const std::string &font_path, uint8 size) {
    _font_size = size;
    _font_path = font_path;
    
    int         error;
    FT_Library  library;
    
    error = FT_Init_FreeType(&library);
    if (error) {
        std::cerr << "error init library" << std::endl;
        throw std::runtime_error("An error occurred during Freetype library initialization.");
    }
    
    FT_Face face;
    error = FT_New_Face(library, font_path.c_str(), 0, &face);
    if ( error == FT_Err_Unknown_File_Format ) {
        std::cerr << "error file format" << std::endl;
        throw std::runtime_error("The font file could be opened and read, but it appears that its font format is unsupported.");
    } else if (error) {
        std::cerr << "error loading file" << std::endl;
        throw std::runtime_error("The font file could not be opened or read, or simply that it is broken.");
    }
    
    FT_Set_Char_Size( face, 0, size * 64, 300, 300);
    
    FT_GlyphSlot slot;
    for(unsigned char ch = 0; ch < 128; ch++) {
        error = FT_Load_Char(face, ch, FT_LOAD_RENDER);
        if (error) {
            std::cerr << "error loading glyph" << std::endl;
            throw std::runtime_error("FT_Load_Glyph failed");
        }
        slot = face->glyph;

        _width.push_back(slot->bitmap.width);
        _height.push_back(slot->bitmap.rows);
        if (ch != ' ')
            _escapement_left.push_back(slot->bitmap_left);
        else
            _escapement_left.push_back(slot->advance.x/64);
        _escapement_top.push_back(slot->bitmap_top);
        _character_tab.push_back(_returnRGBA(slot->bitmap.buffer, slot->bitmap.width * slot->bitmap.rows * 4));
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(library);
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
    Graphic::Texture *tex = new Texture();
    
    tex->setData(getStringWidth(str), getStringHeight(str), stringData(str));
    return tex;
}


uint8 *Graphic::FreetypeFont::stringData(std::string &str) const {
    int max_x = 0;
    int y_max = 0;
    int y_min = 0;
    int esc = 0;
    char c;
    for (int i = 0; str[i] != '\0'; ++i) {
        c = str[i];
        max_x += _width[c];
        if (i != 0)
            esc += _escapement_left[c];
        if (_escapement_top[c] > y_max) {
            y_max = _escapement_top[c];
        }
        if ((_height[c] - _escapement_top[c]) > y_min) {
            y_min = _height[c] - _escapement_top[c];
        }
    }
    
    int max_y = y_max + y_min;
    int origin_y = y_max;
    uint8 *data = new uint8[(max_x + esc) * max_y * 4];
    int save_x = 0;
    int xx = 0;
    int yy = 0;
    for (int ch = 0; str[ch] != '\0'; ++ch) {
        c = str[ch];
        std::cout << c << " " << _width[c] << " " << _escapement_left[c] << std::endl;
        if (ch > 0 && str[ch-1] != ' ') {
            save_x += xx + (_escapement_left[c]*4);
        }
        yy = 0;
        for (int y = (origin_y - _escapement_top[c]); y <= (origin_y - _escapement_top[c] + _height[c]); ++y) {
            xx = 0;
            for (int x = save_x; x < (save_x + (_width[c] * 4)); ++x) {
                if (yy < _height[c]) {
                    data[(y * (max_x + esc) * 4) + x] = _character_tab[c][(yy * _width[c] * 4) + xx];
                } else {
                    data[(y * (max_x + esc) * 4) + x] = 0;
                }
                xx++;
            }
            yy++;
        }
        yy = 0;
    }
    
    return data;
}

int     Graphic::FreetypeFont::getStringWidth(const std::string &str) {
    int save;
    
    save = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (i != 0) {
            save += _width[str[i]] + _escapement_left[str[i]];
        } else  {
            save += _width[str[i]];
        }
    }
    return save;
}

int     Graphic::FreetypeFont::getStringHeight(const std::string &str) {
    int save;
    
    save = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (_height[str[i]] > save) {
            save = _height[str[i]];
        }
    }
    return save*2;
}


uint8   *Graphic::FreetypeFont::letterData(char c) const {
    return _character_tab[c];
}

int     Graphic::FreetypeFont::getWidth(char c) const {
    return _width[c];
}

int     Graphic::FreetypeFont::getHeight(char c) const {
    return _height[c];
}
