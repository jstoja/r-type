#include "Application.h"

Utilities::Application::Application() {
}

Utilities::Application::~Application() {
}

void	Utilities::Application::init(char **av, int32 ac) {
  _av = av;
  _ac = ac;  
  _resourcesPath = av[0];
  _resourcesPath = _resourcesPath.substr(0, _resourcesPath.find_last_of('/'));
# if defined OS_WINDOWS
  _resourcesPath += "\\";
# else
  _resourcesPath += "/";
# endif
}

std::string const&	Utilities::Application::getResourcesPath() const {
  return _resourcesPath;
}

int main(int argc, char **argv) {
  Utilities::Application app = Utilities::Application::getInstance();
  
  app.init(argv, argc);
  std::cout << app.getResourcesPath() << std::endl;
}
