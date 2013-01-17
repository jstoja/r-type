//
// GraphicScene.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 13 23:07:17 2013 Samuel Olivier
//

#ifndef _GRAPHIC_SCENE_H_
# define _GRAPHIC_SCENE_H_

# include <list>

# include <Network/UdpPacket.h>
# include <Network/TcpPacket.h>

# include "GraphicElement.h"
# include "Threading/Mutex.h"
# include "Viewport.h"

class GraphicScene {
public:
	GraphicScene();
	~GraphicScene();

	void	addElement(GraphicElement *element);
	void	sendStaticElements(Network::TcpPacket& packet);
	void	sendElements(Network::UdpPacket& packet, ViewPort* viewport);

private:
    Threading::Mutex            _graphicElementsMutex;
	std::list<GraphicElement*>	_graphicElements;
};

#endif