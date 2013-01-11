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
    
    //! Class modelizing a Scenery (a moving Background)
    class Scenery : public Background {
    public:
        
        //! Create a Scenery
        Scenery(void);

        //! Create a Scenery with an Object id
        Scenery(uint32 id);
        
        //! Destroy the Scenery
        virtual ~Scenery(void);
        
        //! Return the speed of the Scenery
        float32 getSpeed(void) const;

        //! Set the speed of the Scenery
        void    setSpeed(float32 speed);

		//! Return the depth of the Scenery
        float32 getDepth(void) const;

		//! Set the depth of the Scenery
        void	setDepth(float32 depth);
        
		//! Set the width of the Scenery
        void	setWidth(float32 width);
        
        //! Get the width of the Scenery
        float32	getWidth(void) const;
        
    private:
        float32 _speed;
        float32 _depth;
        float32 _width;
    };
    
}

#endif /* defined(__R_Type__Scenery__) */
