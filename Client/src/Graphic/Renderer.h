//
//  Renderer.h
//  R-Type
//
//  Created by Gael du Plessix on 19/12/12.
//
//

#ifndef __R_Type__Renderer__
# define __R_Type__Renderer__

# include <string>
# include "Types.h"
# include "Vec2.h"

# if (defined OS_IOS)
#  define GRAPHIC_RENDERER_IOS
# else
# define GRAPHIC_RENDERER_SFML
# endif

# ifdef GRAPHIC_RENDERER_SFML
# include <SFML/Graphics.hpp>
# endif

namespace Graphic {
    
    class Renderer {
    public:
        
        struct Settings {
            Settings(std::string const& title="RType",
                     Vec2 size=Vec2(1280, 720),
                     uint32 antialiasingLevel=2,
                     bool fullScreen=false);
            
            std::string title;
            Vec2        size;
            uint32      antialiasingLevel;
            bool        fullScreen;
        };
        
        Renderer(Settings const& settings=Settings());
        ~Renderer();
      
    private:
        uint32          _antialiasingLevel;
        
# ifdef GRAPHIC_RENDERER_SFML
        sf::Window*     _window;
# endif
    };
    
}

#endif /* defined(__R_Type__Renderer__) */
