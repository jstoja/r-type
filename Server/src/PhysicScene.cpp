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
	_graphicElements.push_back(element);
}

void	PhysicScene::sendStaticElements(Network::TcpPacket& packet) {
	std::list<PhysicElement*>	toSend;

	for (std::list<PhysicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->getType() == IPhysicElement::Static)
			toSend.push_back(*it);
	packet << toSend;
}

void	PhysicScene::sendElements(Network::UdpPacket& packet) {
	std::list<PhysicElement*>	toSend;

	for (std::list<PhysicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->hasChanged())
			toSend.push_back(*it);
	packet << toSend;
}