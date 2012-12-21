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

namespace Graphic {
    
    class Scene {
    public:
        
        Scene(void);
        virtual ~Scene(void);
        
        void addBackground(Background* background);
        void addScenery(Scenery* scenery);
        void addElement(Element* element);
        
        std::vector<Element*> const &   getElements(void) const;
        
        Matrix4f const& getWorldMatrix(void) const;
        Vec2 const&     getViewport(void) const;
        
    private:
        std::vector<Background*>    _backgrounds;
        std::vector<Scenery*>       _sceneries;
        std::vector<Element*>       _elements;
        Matrix4f                    _worldMatrix;
        Vec2                        _viewport;
    };
    
}

#endif /* defined(__R_Type__Scene__) */
