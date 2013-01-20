//
// PhysicScene.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:36:02 2013 Samuel Olivier
//

#ifndef _PHYSIC_SCENE_H_
# define _PHYSIC_SCENE_H_

# include <list>

# include <Network/UdpPacket.h>
# include <Network/TcpPacket.h>

# include "PhysicElement.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"
# include "Viewport.h"

class PhysicScene {
public:
	PhysicScene();
	~PhysicScene();

	void	addElement(PhysicElement *element);
	void	sendStaticElements(Network::TcpPacket& packet);
	void	sendElements(Network::UdpPacket& packet, Viewport* viewport);

private:
    Threading::Mutex            *_physicElementsMutex;
	std::list<PhysicElement*>	_physicElements;
};

#endif
