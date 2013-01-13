//
//  Clock.cpp
//  R-Type
//
//  Created by Gael du Plessix on 13/01/13.
//
//

#include "Clock.h"
#include "OS.h"
#include "Debug.h"

// Platform dependent implementation of getCurrentTime() and sleep
#ifdef OS_WINDOWS

/*
int gettimeofday (struct timeval *tp, void *tz) {
struct _timeb timebuffer;
_ftime (&timebuffer);
tp->tv_sec = timebuffer.time;
tp->tv_usec = timebuffer.millitm * 1000;
}
*/

#else

# include <sys/time.h>
# include <unistd.h>

uint64 Clock::getCurrentTime(void) {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000;
}

void Clock::sleep(uint64 milliseconds) {
    usleep(milliseconds * 1000);
}

#endif

Clock::Clock(void) : _clockTime(0) {
    reset();
}

Clock::~Clock(void) {
}

uint64 Clock::getEllapsedTime(void) const {
    return Clock::getCurrentTime() - _clockTime;
}

void Clock::reset(void) {
    _clockTime = Clock::getCurrentTime();
}