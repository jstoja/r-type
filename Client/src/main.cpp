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
#if defined OS_MAC
        Application::getInstance().setRelativeResourcesPath("../Resources");
#endif
        Application::getInstance().init(argc, argv);
        Client client;
    }
    catch (std::exception* e) {
        std::cerr << e->what() << std::endl;
    }
    return (0);
}
