//
// GraphicScene.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 13 23:17:20 2013 Samuel Olivier
//

#include "GraphicScene.h"

GraphicScene::GraphicScene() {
}

GraphicScene::~GraphicScene() {
}

void	GraphicScene::addElement(GraphicElement *element) {
	_graphicElements.push_back(element);
}

void	GraphicScene::sendStaticElements(Network::TcpPacket& packet) {
	std::list<GraphicElement*>	toSend;

	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->getType() == IGraphicElement::Static)
			toSend.push_back(*it);
	packet << toSend;
}

void	GraphicScene::sendElements(Network::UdpPacket& packet) {
	std::list<GraphicElement*>	toSend;

	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->hasChanged())
			toSend.push_back(*it);
	packet << toSend;
}