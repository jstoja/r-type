//
// GraphicScene.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 13 23:17:20 2013 Samuel Olivier
//

#include <algorithm>
#include "GraphicScene.h"

GraphicScene::GraphicScene() {
    _graphicElementsMutex = new Threading::Mutex();
}

GraphicScene::~GraphicScene() {
}

void	GraphicScene::addElement(GraphicElement *element) {
    Threading::MutexLocker locker(_graphicElementsMutex);
	_graphicElements.push_back(element);
}

void	GraphicScene::removeElement(GraphicElement *element) {
    Threading::MutexLocker locker(_graphicElementsMutex);
    _graphicElements.erase(std::remove(_graphicElements.begin(), _graphicElements.end(), element), _graphicElements.end());
}

void	GraphicScene::sendStaticElements(Network::TcpPacket& packet) {
	std::list<GraphicElement*>	toSend;

    Threading::MutexLocker locker(_graphicElementsMutex);
	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->getType() == IGraphicElement::Static)
			toSend.push_back(*it);
	packet << toSend;
}

void	GraphicScene::sendElements(Network::UdpPacket& packet, Viewport* viewport) {
	std::list<GraphicElement*>	toSend;

    Threading::MutexLocker locker(_graphicElementsMutex);
	for (std::list<GraphicElement*>::iterator it = _graphicElements.begin();
		it != _graphicElements.end(); ++it)
		if ((*it)->hasChanged() && viewport->isInViewport(Rect2((*it)->getPosition(), (*it)->getSize())))
			toSend.push_back(*it);
	packet << toSend;
}