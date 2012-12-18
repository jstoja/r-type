#include "Ressource.h"


Ressource::Ressource() {
}

Ressource::Ressource(std::string const& name) {
  _name = name;
}

Ressource::~Ressource() {
}

Ressource::Ressource(Ressource const& cpy)
{
  setName(cpy.getName());
}

std::string const& Ressource::getName() const {
  return _name;
}

void	Ressource::setName(std::string const& name) {
  _name = name;
}

Ressource&	Ressource::operator=(Ressource const& cpy)
{
  setName(cpy.getName());
  return *this;
}

bool	Ressource::operator==(Ressource const& cmp)
{
  if (getName() == cmp.getName())
    return true;
  return false;
}
