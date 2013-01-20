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

# include <OS.h>
# include <IPhysicElement.h>
# include <Object.h>
# include <Network/UdpPacket.h>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

class COMMON_EXPORT_IMPORT PhysicElement : public IPhysicElement, public Object {
public:
	PhysicElement();
    PhysicElement(PhysicElement const& other);
	virtual ~PhysicElement();

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

	static bool collision(PhysicElement& elem1, PhysicElement& elem2);

private:
	struct Box {
	  Box(float32 posX, float32 posY, float32 w, float32 h, float32 angle);
	  void rotate(Box& other);
	  void update();
	  static bool simpleCollision(Box& box1, Box& box2);

	  float32 posX;
	  float32 posY;
	  float32 w;
	  float32 h;
	  float32 angle;
	  Box* out;
	};

    enum    _mutexVariable {
        ePosition = 0,
        eSize,
        eRotation,
        eHasChanged,
        eType,
        eLastAttribute
    };
    
    std::vector<Threading::Mutex*>	_attributesMutex;
	Vec2	_pos;
	Vec2	_size;
	float32	_rotation;
	bool	_hasChanged;
	char	_type;
};

COMMON_EXPORT_IMPORT Network::APacket& operator<<(Network::APacket & packet, PhysicElement & element);

#endif
