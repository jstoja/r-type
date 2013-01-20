//
// Viewport.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 17 14:18:51 2013 Samuel Olivier
//

#ifndef _VIEWPORT_H_
# define _VIEWPORT_H_

# include <Types.h>
# include <IViewport.h>
# include <Clock.h>
# include <vector>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

class Viewport : public IViewport {
public:
	Viewport(float32 speed = 0.1);
	virtual ~Viewport();

	virtual void	setPosition(float32 x);
	virtual float32	getPosition() const;

	virtual void	setWidth(float32 width);
	virtual float32	getWidth() const;

	virtual void	setSpeed(float32 width);
	virtual float32	getSpeed() const;

	virtual bool	isInViewport(Rect2 const& object) const;
	virtual bool	isInViewport(float32 x) const;

	void			update(Clock& clock);

private:
    enum    _mutexVariable {
        eX = 0,
        eWidth,
        eSpeed,
        eLastAttribute
    };
    std::vector<Threading::Mutex*>	_attributesMutex;
    
	float32	_x;
	float32	_width;
	float32	_speed;
};

#endif