//
// Texture.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 17:51:38 2013 Samuel Olivier
//

#include <Application.h>
#include <ResourcesManager.h>

#include "Texture.h"

Texture::Texture(std::string const& filepath) {
	std::string tmp = Application::getInstance().getResourcesPath();
	_img = ResourcesManager::getInstance().loadResource(filepath);
}

Texture::~Texture() {
	delete _img;
}

Network::TcpPacket&		operator<<(Network::TcpPacket & packet, Texture const& texture) {
	packet << texture.getId() << texture.getImg()->getId();
	return (packet);
}

Resource*	Texture::getImg() const {
	return (_img);
}