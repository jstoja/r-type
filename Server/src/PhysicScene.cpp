//
// PhysicScene.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  lun. janv. 14 00:40:09 2013 Samuel Olivier
//

#include "PhysicScene.h"

PhysicScene::PhysicScene() {
}

PhysicScene::~PhysicScene() {
}

void	PhysicScene::addElement(PhysicElement *element) {
    _physicElementsMutex.lock();
	_physicElements.push_back(element);
    _physicElementsMutex.unlock();
}

void	PhysicScene::sendStaticElements(Network::TcpPacket& packet) {
	std::list<PhysicElement*>	toSend;
    
    _physicElementsMutex.lock();
	for (std::list<PhysicElement*>::iterator it = _physicElements.begin();
		it != _physicElements.end(); ++it)
		if ((*it)->getType() == IPhysicElement::Static)
			toSend.push_back(*it);
    _physicElementsMutex.unlock();
	packet << toSend;
}

void	PhysicScene::sendElements(Network::UdpPacket& packet, ViewPort* viewPort) {
	std::list<PhysicElement*>	toSend;

    _physicElementsMutex.lock();
	for (std::list<PhysicElement*>::iterator it = _physicElements.begin();
		it != _physicElements.end(); ++it)
		if ((*it)->hasChanged() && viewPort->isInViewport(Rect2((*it)->getPosition(), (*it)->getSize())))
			toSend.push_back(*it);
    _physicElementsMutex.unlock();
	packet << toSend;
}