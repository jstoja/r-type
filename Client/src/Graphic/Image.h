//
//  Image.h
//  R-Type
//
//  Created by Gael du Plessix on 11/01/13.
//
//

#ifndef __R_Type__Image__
#define __R_Type__Image__

# include "OS.h"
# include "Types.h"
# include "Vec2.h"
# include "ByteArray.h"

# ifndef OS_IOS
#  include <SFML/Graphics.hpp>
# endif

namespace Graphic {
    
    //! Representation of an image with platform-independent loading from a resource file
    class Image {
    public:
        
        Image(std::string const& resourceName="");
        ~Image(void);
        
        void            loadFromResource(std::string const& resourceName);
        void            loadFromData(ByteArray const& data);
        
        uint8 const*    getPixelsPtr(void) const;
        uint32          getWidth(void) const;
        uint32          getHeight(void) const;
        Vec2            getSize(void) const;
        
    private:
        uint8 const*    _pixels;
        uint32          _width;
        uint32          _height;
    };
    
}


#endif /* defined(__R_Type__Image__) */
