//
//  Scenery.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Graphic__Scenery__
# define __R_Type__Graphic__Scenery__

# include "Background.h"

namespace Graphic {
    
    class Scenery : public Background {
    public:
        
        Scenery(void);
        Scenery(uint32 id);
        
        virtual ~Scenery(void);
        
        float32 getSpeed(void) const;
        void    setSpeed(float32 speed);
        
    private:
        float32 _speed;
        float32 _depth;
    };
    
}

#endif /* defined(__R_Type__Scenery__) */
