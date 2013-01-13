//
//  Clock.h
//  R-Type
//
//  Created by Gael du Plessix on 13/01/13.
//
//

#ifndef __R_Type__Clock__
# define __R_Type__Clock__

# include <time.h>
# include "Types.h"

//! Utility class for mesuring time ellapsed during a certain period
class Clock {
public:
    
    //! Get the current time in milliseconds
    static uint64   getCurrentTime(void);
    
    //! Platform independent sleep in milliseconds
    static void     sleep(uint64 milliseconds);
    
    //! Create a new clock
    Clock(void);
    
    //! Destruct a clock
    ~Clock(void);
    
    //! Get ellapsed time
    /*!
        Get the ellapsed time in milliseconds since creation of the object
        or the last call of reset()
     */
    uint64  getEllapsedTime(void) const;
    
    //! Reset the clock
    void    reset(void);
    
private:
    uint64  _clockTime;
};

#endif /* defined(__R_Type__Clock__) */
