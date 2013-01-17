//
//  Scene.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Scene__
# define __R_Type__Scene__

# include <vector>
# include "Object.h"
# include "Background.h"
# include "Scenery.h"
# include "Element.h"
# include "Matrix.hpp"
# include "Threading/Mutex.h"

namespace Graphic {
   
   	//! Class modelizing a scene
    class Scene {
    public:
        
        //! Create a Scene
        Scene(void);

        //! Destroy a Scene
        virtual ~Scene(void);
 
 		//! Add a Background to the Scene
        void addBackground(Background* background);

        //! Add a Scenery to the Scene
        void addScenery(Scenery* scenery);

        //! Add an Element to the Scene
        void addElement(Element* element);
        
        //! Remove an element from the scene
        void removeElement(Element* element);
        
        //! Return all the sceneries of the scene
        std::vector<Scenery*> const &   getSceneries(void) const;
        
		//! Return all the Elements linked to the Scene as a Vector of Elements
        std::vector<Element*> const &   getElements(void) const;
        
        //! Return the scene-space matrix
        Matrix4f const& getWorldMatrix(void) const;
        
        //! Return the transformation matrix for viewport space
        Matrix4f        getViewportMatrix(void) const;
        
        //! Set the viewport size of the Scene
        void setViewport(Vec2 const& size);

        //! Return the viewport size of the Scene
        Vec2 const& getViewport(void) const;
        
        //! Return the viewport position ('camera' position)
        Vec2 const& getViewportPosition(void) const;
        
        //! Set the viewport position
        void        setViewportPosition(Vec2 const& pos);
        
    private:
        
        //! Init the world matrix to the scene space
        void _initWorldMatrix(void);        
        
        std::vector<Background*>    _backgrounds;
        std::vector<Scenery*>       _sceneries;
        std::vector<Element*>       _elements;
        Matrix4f                    _worldMatrix;
        Vec2                        _viewport;
        Vec2                        _viewportPosition;
        Threading::Mutex*           _mutex;
    };
    
}

#endif /* defined(__R_Type__Scene__) */
