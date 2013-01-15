//
//  main.cpp
//  RType
//
//  Created by Gael du Plessix on 17/12/12.
//
//

#include <iostream>
#include <exception>
#include "Application.h"
#include "Client.h"

int	main(int argc, char *argv[]) {
    try {
        Application::getInstance().init(argc, argv);
#if defined OS_MAC
        Application::getInstance().setRelativeResourcesPath("../Resources");
#else
        Application::getInstance().setRelativeResourcesPath("Resources");
#endif
        Client client;
    }
    catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    } catch (...) {
		std::cerr << "Unhandled Exception" << std::endl;
	}
    return (0);
}
