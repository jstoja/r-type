//
// MapCreator.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 21:24:42 2013 Samuel Olivier
//

#include <string>
#include <list>
#include <iostream>

#include <Application.h>
#include <ResourcesManager.h>
#include <Map.h>
#include <LibraryFactory.h>

int	main(int ac, char **av) {
	App.init(ac, av);
	App.setRelativeResourcesPath("../Server/Resources");
	std::string filename = "../Server/Resources/Levels/Level_1/Level_1.map";

	if (ac > 1)
		filename = av[1];
	Map	map;
	bool ok = map.load(Application::getInstance().getRelativePath(filename));
	if (ok == false)
		std::cerr << map.getError() << std::endl;
	else {
		std::cout << "Name: " << map.getName() << std::endl;
		std::cout << "Sprite Size: " << map.getSprites().size() << std::endl;
		if (map.getSprites().size() > 0) {
			std::cout << "Sprite Name: " << map.getSprites().begin()->first << std::endl;
			std::cout << "Sprite Nb Frame: " << map.getSprites().begin()->second->getFrames().size() << std::endl;
			std::cout << "P1: " << map.getSprites().begin()->second->getFrames().begin()->p1.x << ":"
					  << map.getSprites().begin()->second->getFrames().begin()->p1.y << " "
					  << "P2: " << map.getSprites().begin()->second->getFrames().begin()->p2.x << ":"
					  << map.getSprites().begin()->second->getFrames().begin()->p2.y << " "
					  << std::endl;
		}
		std::cout << "Object Size: " << map.getObjects().size() << std::endl;
		if (map.getObjects().size() > 0) {
			std::cout << "Plugin Name: " << map.getObjects().begin()->name << std::endl;
			std::cout << "Object xStart: " <<  map.getObjects().begin()->xStart << std::endl;
		}
	}
	return (0);
}