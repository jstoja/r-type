#include <iostream>
#include <string>

#include <Exception.h>
#include "Types.h"
#include "Font.h"

Graphic::FreetypeFont::FreetypeFont(uint8 size, const std::string &path)
: _font_path(path), _font_size(size), _font_loaded(false) {
    int         error;

    error = FT_Init_FreeType(&_library);
    if (error)
        throw new Exception("An error occurred during Freetype library initialization.");
    changeFont(_font_path, _font_size);
}

void Graphic::FreetypeFont::changeFont(const std::string &font_path, uint8 size) {
    _font_loaded = false;
    _font_size = size;
    _font_path = font_path;
    
    int         error;
    error = FT_New_Face(_library, font_path.c_str(), 0, &_face);
    if ( error == FT_Err_Unknown_File_Format )
        throw new Exception("The font file could be opened and read, but it appears that its font format is unsupported.");
    else if (error)
		throw new Exception("The font file \"" + font_path + "\"could not be opened or read, or simply that it is broken.");
    FT_Set_Char_Size(_face, 0, size * 64, 300, 300);
    
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
            _bearing_left.push_back(slot->bitmap_left);
        else
            _bearing_left.push_back(slot->advance.x/64);
        _bearing_top.push_back(slot->bitmap_top);
        _character_tab.push_back(_returnRGBA(slot->bitmap.buffer, slot->bitmap.width * slot->bitmap.rows * 4));
    }
    _font_loaded = true;
}

Graphic::FreetypeFont::~FreetypeFont(void) {
    if (_font_loaded == true) {
        for(unsigned char ch = 0; ch < _character_tab.size(); ++ch) {
            delete[] _character_tab[ch];
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


uint8 *Graphic::FreetypeFont::stringData(std::string &str) const {
    int max_x = 0;
    int y_max = 0;
    int y_min = 0;
    int esc = 0;
    char c;
    for (int i = 0; str[i] != '\0'; ++i) {
        c = str[i];
        max_x += _width[c];
        if (i != 0) {
            esc += _bearing_left[c];
        }
        if (_bearing_top[c] > y_max) {
            y_max = _bearing_top[c];
        }
        if ((_height[c] - _bearing_top[c]) > y_min) {
            y_min = _height[c] - _bearing_top[c];
        }
    }

    int max_line_width = (max_x + esc) * 4;
    int max_y = y_max + y_min;

    uint8 *data = new uint8[max_line_width * max_y];
    int save_x = 0;
    //int y_char = 0;
    int line_width = 0;
    // Iterate over all the chars in the string to add then in the new texture (a RGBA Bitmap)
    for (int ci = 0; str[ci] != '\0'; ++ci) {
        c = str[ci];
        if (ci > 0 && str[ci-1] != ' ') {
            save_x += line_width + (_bearing_left[c] * 4);
        }
        // Iterate over all the lines of one char an copy the line in the Texture
        for (int y = (y_max - _bearing_top[c]), y_char = 0; y < (y_max - _bearing_top[c] + _height[c]); ++y, ++y_char) {
            line_width = _width[c] * 4;
            if (y_char < _height[c]) {
                memcpy(data + ((y * max_line_width) + save_x),
                       _character_tab[c] + ((y_char * line_width)),
                       line_width);
            } else {
                memset(data + ((y * max_line_width) + save_x), 0, line_width);
            }
        }
    }
    return data;
}

int     Graphic::FreetypeFont::getStringWidth(const std::string &str) {
    int save;
    
    save = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (i != 0) {
            save += _width[str[i]] + _bearing_left[str[i]];
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
