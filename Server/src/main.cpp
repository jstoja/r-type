//
// main.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
//
// Started on  mer. déc. 19 12:35:36 2012 Samuel Olivier
//

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <cstdio>
#include <Application.h>

#include "Server.h"

int	main(int argc, char *argv[]) {
	App.init(argc, argv);
	App.setRelativeResourcesPath("./Resources");
	Server server;

	getchar();
	return (0);
}
