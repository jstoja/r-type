//
// Application.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:09 2012 Samuel Olivier
//

#include "Application.h"

Application::Application() {
}

Application::~Application() {
}

void Application::concatPath() {
    _resourcesPath = _av[0];
# if defined OS_WINDOWS
    // ajouter la fonction pour gerer ca sous windaube
# else
    _resourcesPath = _resourcesPath.substr(0, _resourcesPath.find_last_of('/'));
    _resourcesPath += "/";
# endif

}

void Application::init(char **av, int32 ac) {
    _av = av;
    _ac = ac;
    concatPath();
}

std::string const& Application::getResourcesPath() const {
    return _resourcesPath;
}
