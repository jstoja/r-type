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
    _graphicElementsMutex.lock();
	_graphicElements.push_back(element);
    _graphicElementsMutex.unlock();
}

void	GraphicScene::sendStaticElements(Network::TcpPacket& packet) {
	std::list<GraphicElement*>	toSend;

    _graphicElementsMutex.lock();
	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->getType() == IGraphicElement::Static)
			toSend.push_back(*it);
    _graphicElementsMutex.unlock();
	packet << toSend;
}

void	GraphicScene::sendElements(Network::UdpPacket& packet, Viewport* viewport) {
	std::list<GraphicElement*>	toSend;

    _graphicElementsMutex.lock();
	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->hasChanged() && viewport->isInViewport(Rect2((*it)->getPosition(), (*it)->getSize())))
			toSend.push_back(*it);
    _graphicElementsMutex.unlock();
	packet << toSend;
}