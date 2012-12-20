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

namespace Graphic {
    
    class Scene {
    public:
        
        Scene(void);
        virtual ~Scene(void);
        
        void addBackground(Background* background);
        void addScenery(Scenery* scenery);
        void addElement(Element* element);
        
    private:
        std::vector<Background*>    _backgrounds;
        std::vector<Scenery*>       _sceneries;
        std::vector<Element*>       _elements;
    };
    
}

#endif /* defined(__R_Type__Scene__) */
