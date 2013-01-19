//
// IScenery.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 14:32:31 2013 Samuel Olivier
//

#ifndef _I_SCENERY_H_
# define _I_SCENERY_H_

# include <Types.h>

class ITexture;

class IScenery {
public:
	virtual ~IScenery() {}

	virtual void	setTexture(ITexture* texture) = 0;
	
	virtual void	setSpeed(float32 speed) = 0;
	virtual float32	getSpeed() const = 0;

	virtual void	setWidth(float32 width) = 0;
	virtual float32	getWidth() const = 0;

	virtual void	setXStart(float32 xStart) = 0;
	virtual float32	getXStart() const = 0;

	virtual void	setXEnd(float32 xEnd) = 0;
	virtual float32	getXEnd() const = 0;
    
    virtual void	setDepth(float32 depth) = 0;
	virtual float32	getDepth() const = 0;
    
	virtual void	setOpacity(float32 opacity) = 0;
	virtual float32	getOpacity() const = 0;
};

#endif