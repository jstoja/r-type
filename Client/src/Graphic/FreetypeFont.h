//
//  FreetypeFont.h
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

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

        FreetypeFont(const std::string &resourceName, uint8 size = 24, Vec3 color=Vec3(1, 1, 1));

        void loadFont(const std::string &resourceName);

        ~FreetypeFont(void);

        Graphic::Texture *getStringTexture(std::string &str);

        uint8   *letterData(char c) const;
        uint8   *stringData(std::string const& str) const;

        int     getWidth(char c) const;
        int     getHeight(char c) const;

        int     getStringHeight(std::string const& str);
        int     getStringWidth(std::string const& str);

    private:
        
        //! Return an rgba image from a FreeType bitmap
        /*!
         Only handle FT_PIXEL_MODE_GRAY bitmaps.
         */
        uint8                   *_alphaToRGBA(FT_Bitmap bitmap);

        static FT_Library       _library;
        static bool             _libraryLoaded;

        int                     _fontSize;
        FT_Face                 _face;
        std::vector<uint8*>     _characterTab;
        std::vector<int>        _width;
        std::vector<int>        _height;
        std::vector<int>        _bearingLeft;
        std::vector<int>        _bearingTop;
        Vec3                    _color;
    };
}

#endif
