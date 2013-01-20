//
// GraphicElement.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 16:56:43 2013 Samuel Olivier
//

#ifndef _GRAPHIC_ELEMENT_H_
# define _GRAPHIC_ELEMENT_H_

# include <IGraphicElement.h>
# include <Object.h>
# include <Network/UdpPacket.h>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

class Sprite;

class GraphicElement : public IGraphicElement, public Object {
public:
	GraphicElement();
	~GraphicElement();

	virtual void	setPosition(Vec3 const& pos);
	virtual void	move(Vec3 const& pos);
	virtual Vec3 const& getPosition() const;

	virtual void	setSize(Vec2 const& rect);
	virtual Vec2 const&	getSize() const;

	virtual void	setRotation(float32 rotation);
	virtual float32	getRotation() const;

	virtual bool	hasChanged() const;
	virtual void	setChanged(bool changed);
	
	virtual void	setSprite(ISprite *sprite);
	Sprite*			getSprite() const;

	virtual void	setSpriteFrameIndex(char idx);
	virtual uint8	getSpriteFrameIndex() const;

	virtual void	setType(Type c);
	virtual Type	getType() const;

    virtual Rect2   getRect(void) const;
    
private:
    enum    _mutexVariable {
        ePosition = 0,
        eSize,
        eRotation,
        eHasChanged,
        eSprite,
        eSpriteIndex,
        eType,
        eLastAttribute
    };
    
    std::vector<Threading::Mutex*>	_attributesMutex;
	Vec3                            _pos;
	Vec2                            _size;
	float32                         _rotation;
	bool                            _hasChanged;
	Sprite	                        *_sprite;
	uint8                            _spriteIndex;
	uint8                            _type;
};

Network::APacket&		operator<<(Network::APacket & packet, GraphicElement & element);

#endif