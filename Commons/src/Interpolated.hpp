//
//  Interpolated.hpp
//  R-Type
//
//  Created by Gael du Plessix on 20/01/13.
//
//

#ifndef R_Type_Interpolated_hpp
# define R_Type_Interpolated_hpp

# include <list>
# include <OS.h>
# include "Types.h"
# include "Clock.h"

template <class T>
class Interpolated {
public:
    
    Interpolated() : _isInit(false), _previousValue(), _clock() {
        
    }
    
    ~Interpolated(void) {
        
    }
    
    void initValue(T const& newValue, float32 time) {
        _speed = T();
        _previousValue = newValue;
        _clock.reset();
        _previousTime = time;
        _isInit = true;
    }
    
    void setValue(T const& newValue, float32 time) {
        if (!_isInit)
            initValue(newValue, time);
        if (time < _previousTime)
            return ;
        _speed = (newValue - _previousValue) / (time - _previousTime);
        _previousValue = newValue;
        _previousTime = time;
        _clock.reset();
    }
    
    T getValue(void) const {
        return _previousValue + _speed * _clock.getEllapsedTime();
    }
    
private:
    bool    _isInit;
    T       _previousValue;
    T       _speed;
    float32 _previousTime;
    Clock   _clock;
};

#endif
