//
// PhysicElement.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:27:58 2013 Samuel Olivier
//

#ifndef _PHYSIC_ELEMENT_H_
# define _PHYSIC_ELEMENT_H_

# include <IPhysicElement.h>
# include <Object.h>
# include <Network/UdpPacket.h>

class PhysicElement : public IPhysicElement, public Object {
public:
	PhysicElement();
	~PhysicElement();

	virtual void	setPosition(Vec2 const& pos);
	virtual void	move(Vec2 const& pos);
	virtual Vec2 const& getPosition() const;

	virtual void	setSize(Vec2 const& rect);
	virtual Vec2 const&	getSize() const;

	virtual void	setRotation(float32 rotation);
	virtual float32	getRotation() const;

	virtual bool	hasChanged() const;
	virtual void	setChanged(bool changed);

	virtual void	setType(Type c);
	virtual Type	getType() const;

private:
	Vec2	_pos;
	Vec2	_size;
	float32	_rotation;
	bool	_hasChanged;
	char	_type;
};

Network::APacket&		operator<<(Network::APacket & packet, PhysicElement & element);

#endif