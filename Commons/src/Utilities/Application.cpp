//
// Application.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:09 2012 Samuel Olivier
//

#include "Application.h"

Utilities::Application::Application() {
}

Utilities::Application::~Application() {
}

void	Utilities::Application::concatPath() {
  _resourcesPath = _av[0];
# if defined OS_WINDOWS
  // ajouter la fonction pour gerer ca sous windaube
# else
  _resourcesPath = _resourcesPath.substr(0, _resourcesPath.find_last_of('/'));
  _resourcesPath += "/";
# endif

}

void	Utilities::Application::init(char **av, int32 ac) {
  _av = av;
  _ac = ac;  
  concatPath();
}

std::string const&	Utilities::Application::getResourcesPath() const {
  return _resourcesPath;
}
