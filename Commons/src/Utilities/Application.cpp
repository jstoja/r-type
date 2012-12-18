#include "Application.h"

Utilities::Application::Application() {
}

Utilities::Application::~Application() {
}

void	Utilities::Application::init(char **av, int32 ac)
{
  _av = av;
  _ac = ac;
}
