#include "UUIDGenerator.h"
#include "Resource.h"

Utilities::Resource::Resource() {
}

Utilities::Resource::Resource(std::string const& name) {
  _name = name;
  _id = Utilities::UUIDGenerator::getInstance().getUUID();
}

Utilities::Resource::~Resource() {
}

Utilities::Resource::Resource(Resource const& cpy)
{
  setName(cpy.getName());
  _id = cpy._id;
}

std::string const& Utilities::Resource::getName() const {
  return _name;
}

void	Utilities::Resource::setName(std::string const& name) {
  _name = name;
}

Utilities::Resource&	Utilities::Resource::operator=(Resource const& cpy)
{
  setName(cpy.getName());
  return *this;
}

bool	Utilities::Resource::operator==(Resource const& cmp)
{
  if (getId() == cmp.getId())
    return true;
  return false;
}

uint32_t Utilities::Resource::getId() const
{
  return _id;
}
