#ifndef _FONT_H_
# define _FONT_H_

# include <string>
# include <vector>

# include <ft2build.h>
# include FT_FREETYPE_H
# include <freetype/ftglyph.h>

# include "Types.h"
# include "Object.h"
# include "Texture.h"


namespace Graphic {
    class FreetypeFont {
        public:
        FreetypeFont(uint8 size = 14, const std::string &str = "./Marion.ttc");

            void changeFont(const std::string &font_path, uint8 size);
        
            ~FreetypeFont();
        
            Graphic::Texture *getStringTexture(std::string &str);
        
            uint8   *letterData(char c) const;
            uint8   *stringData(std::string const& str) const;

            int     getWidth(char c) const;
            int     getHeight(char c) const;
        
            int     getStringHeight(std::string const& str);
            int     getStringWidth(std::string const& str);
    private:
            uint8                   *_returnRGBA(uint8* bitmap, int size);

            bool                    _font_loaded;
            FT_Library              _library;
            FT_Face                 _face;
            std::string             _font_path;
            int                     _font_size;
            std::vector<uint8*>     _character_tab;
            std::vector<int>        _width;
            std::vector<int>        _height;
            std::vector<int>        _bearing_left;
            std::vector<int>        _bearing_top;
    };
}

#endif