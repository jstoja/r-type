#ifndef _FONT_H_
# define _FONT_H_

# include <string>
# include <vector>

# include "Types.h"
# include "Object.h"

namespace Graphic {
    class FreetypeFont {
        public:
            //FreetypeFont();
            FreetypeFont(const std::string &font_path, uint8 size);
        
            ~FreetypeFont() {}
        
            uint8   *letterData(char c) const;
            uint8   *stringData(std::string &str) const;

            int     getWidth(char c) const;
            int     getHeight(char c) const;
        
            int     getStringHeight(const std::string &str);
            int     getStringWidth(const std::string &str);
    private:
            uint8                   *_returnRGBA(uint8* bitmap, int size);

            std::string             _font_path;
            int                     _font_size;
            std::vector<uint8*>     _character_tab;
            std::vector<int>        _width;
            std::vector<int>        _height;
    };
}

#endif