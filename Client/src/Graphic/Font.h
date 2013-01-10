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
        FreetypeFont(uint8 size = 14, const std::string &str = "");

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

            bool                    _fontLoaded;
            FT_Library              _library;
            FT_Face                 _face;
            std::string             _fontPath;
            int                     _fontSize;
            std::vector<uint8*>     _characterTab;
            std::vector<int>        _width;
            std::vector<int>        _height;
            std::vector<int>        _bearingLeft;
            std::vector<int>        _bearingTop;
    };
}

#endif
