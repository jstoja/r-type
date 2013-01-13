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
	virtual char	getSpriteFrameIndex() const;

private:
	Vec3	_pos;
	Vec2	_size;
	float32	_rotation;
	bool	_hasChanged;
	Sprite	*_sprite;
	char	_spriteIndex;
};

Network::APacket&		operator<<(Network::APacket & packet, GraphicElement & element);

#endif