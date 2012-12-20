//
//  Rect.h
//  R-Type
//
//  Created by Gael du Plessix on 20/12/12.
//
//

#ifndef __R_Type__Rect__
# define __R_Type__Rect__

# include "Types.h"

struct Rect {
    
    Rect(float32 x=0, float32 y=0, float32 width=0, float32 height=0);
    ~Rect();
    
    float32 x;
    float32 y;
    float32 width;
    float32 height;
};

#endif /* defined(__R_Type__Rect__) */
