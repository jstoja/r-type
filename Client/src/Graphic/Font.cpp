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
    
    FT_Set_Char_Size( face, size << 6, size << 6, 300, 300);
    
    FT_Glyph glyph;
    for(unsigned char ch = 0; ch < 128; ch++) {
        error = FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_RENDER);
        if (error) {
            std::cerr << "error loading glyph" << std::endl;
            throw std::runtime_error("FT_Load_Glyph failed");
        }
        FT_GlyphSlot slot = face->glyph;
        _width.push_back(slot->bitmap.width);
        _height.push_back(slot->bitmap.rows);
        _escapement.push_back(slot->advance.x >> 6);
        _character_tab.push_back(_returnRGBA(slot->bitmap.buffer, slot->bitmap.width * slot->bitmap.rows));
    }
    
    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

uint8 *Graphic::FreetypeFont::_returnRGBA(uint8* bitmap, int size) {
    uint8 *data = new uint8[4 * size];
    int i, j;
    
    for (i = 0, j = 0; i < size*4; i += 4, j++) {
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

uint8 *Graphic::FreetypeFont::stringData(std::string &str) const {
    int max_x = 0;
    int max_y = 0;
    int esc = 0;
    char c;
    std::vector<int> save;
    for (int i = 0; str[i] != '\0'; ++i) {
        c = str[i];
        save.push_back(0);
        
        max_x += _width[c];
        if (str[i+1])
            esc += _escapement[c];
        if (_height[c] > max_y) {
            max_y = _height[c];
        }
    }
    
    uint8 *data = new uint8[(max_x + esc) * max_y * 4];
    int xx = 0;
    int char_n = 0;
    c = str[char_n];
    int max_save = _width[c] * _height[c] * 4;
    for (int i = 0; i < (max_x + esc) * max_y * 4; i += 4, ++xx) {
        if (xx >= _width[c]) {
            xx = 0;
            
            //for (int w = 0; w < (_escapement[c] * max_y); ++w) {
                //data[i + w] = 0;
            //}
            
            
            
            char_n += 1;
            if (char_n == str.size()) {
                char_n = 0;
            } else {
                i += (_escapement[c]*4);
            }
            c = str[char_n];
            max_save = _width[c] * _height[c] * 4;
        }
        for (int k = 0; k < 4; ++k) {
            if (save[char_n] < max_save) {
                data[i + k] = _character_tab[c][save[char_n] + k];
            } else {
                data[i + k] = 0;
            }
        }
        save[char_n] += 4;
    }
    return data;
}

int     Graphic::FreetypeFont::getStringWidth(const std::string &str) {
    int save;
    
    save = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i+1])
            save += _width[str[i]] + _escapement[str[i]];
        else
            save += _width[str[i]];
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
    return save;
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
