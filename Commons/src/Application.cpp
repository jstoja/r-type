//
// Application.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. d�c. 19 12:19:09 2012 Samuel Olivier
//

#include "Application.h"

Application::Application() {
}

Application::~Application() {
}

void Application::concatPath() {
# if defined OS_WINDOWS
    // ajouter la fonction pour gerer ca sous windaube
# else
    _binaryPath = _av[0];
    _binaryPath = _binaryPath.substr(0, _binaryPath.find_last_of('/'));
    _binaryPath += '/';
# endif

}

void Application::init(char **av, int32 ac) {
    _av = av;
    _ac = ac;
    concatPath();
}

std::string Application::getResourcesPath() const {
    return _binaryPath + _resourcesPath;
}

void Application::setRelativeResourcesPath(std::string const& path) {
    _resourcesPath = path;
}