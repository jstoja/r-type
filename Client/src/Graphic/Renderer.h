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

# include "Scene.h"
# include "Buffer.hpp"
# include "ShaderProgram.h"
# include "IProvider.h"
# include "Types.h"
# include "Vec2.h"
# include "Rect.h"

# if (defined OS_IOS)
#  define GRAPHIC_RENDERER_IOS
# else
# define GRAPHIC_RENDERER_SFML
# endif

# ifdef GRAPHIC_RENDERER_SFML
# include <SFML/Graphics.hpp>
# endif

namespace Graphic {
    
    //! Class of the Renderer that put a scene into a window
    class Renderer : public Event::IProvider {
    public:
        
        struct Settings {

        	//! Creates the Settings
        	/*!
        	 \param title The title of the window. Default is 'RType'
        	 \param size The size of the window. Default is '1280x720'
        	 \param antialiasingLevel The antialiasing level. Default is '2'
        	 \param fullScreen The fullscreen state. Default is false.
        	 */
            Settings(std::string const& title="RType",
                     Vec2 size=Vec2(1280, 720),
                     uint32 antialiasingLevel=2,
                     bool fullScreen=false);
            
            std::string title;
            Vec2        size;
            uint32      antialiasingLevel;
            bool        fullScreen;
        };
        
        //! Create the renderer with the specified Settings
        Renderer(Settings const& settings=Settings());
        
        //! Platform-specific destructor
        virtual ~Renderer(void);
        
        //! General destructor
        void destruct();
        
        //! Platform-specific operations
        void    createContext(Settings const& settings=Settings());

        //! Refreshing the Renderer
        void    refresh(void);

        //! Return the size vector of the Renderer
        Vec2    getViewportSize(void) const;
        
        //! Process the pending events
        /*!
         \param manager Event Manager with/without pending events
         */
        virtual void processEvents(Event::Manager* manager);
        
        //! Set the Scene to be rendered
        /*!
         \param scene The Scene object
         */
        void    setScene(Scene const* scene);

        //! Rendering the Scene
        void    render(void);

        //! Updating the window
        void    updateViewport(void);
        
        //! Coords transformations
        Vec2    viewportToScene(Vec2 const& coords) const;
        Rect    viewportToScene(Rect const& coords) const;
        Vec2    sceneToViewport(Vec2 const& coords) const;
        Rect    sceneToViewport(Rect const& coords) const;
      
    private:
        //! OpenGL stuff
        void _fillVertexesBuffer(float32 x=0.5, float32 y=0.5);
        void _fillTextureCoordsBuffer(float32 repeatX=1, float32 repeatY=1);
        void _fillIndexesBuffer(void);
        
        uint32              _antialiasingLevel;
        Scene const*        _scene;
        
        //! OpenGL resources
        Graphic::Bufferf*       _vertexesBuffer;
        Graphic::Bufferf*       _textureCoordsBuffer;
        Graphic::Bufferui*      _indexesBuffer;
        Graphic::ShaderProgram* _shaderProgram;
        
        uint32                  _vertexPositionLocation;
        uint32                  _vertexTextureCoordsLocation;
        uint32                  _worldMatrixLocation;
        uint32                  _transformationMatrixLocation;
        uint32                  _textureSamplerLocation;
        
# ifdef GRAPHIC_RENDERER_SFML
        sf::Window*     _window;
# endif
    };
    
}

#endif /* defined(__R_Type__Renderer__) */
