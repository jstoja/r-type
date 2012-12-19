#include <fstream>
#include "UUIDGenerator.h"
#include "Resource.h"
#include "Application.h"

Utilities::Resource::Resource() {
}

Utilities::Resource::Resource(std::string const& name) {  
  _name = name;
  _id = Utilities::UUIDGenerator::getInstance().getUUID();
  readFile();
}

Utilities::Resource::~Resource() {
}

Utilities::Resource::Resource(Resource const& cpy) {
  setName(cpy.getName());
  _id = cpy.getId();
  setArray(cpy.getFile());
}

std::string const& Utilities::Resource::getName() const {
  return _name;
}

void	Utilities::Resource::setName(std::string const& name) {
  _name = name;
}

Utilities::Resource&	Utilities::Resource::operator=(Resource const& cpy) {
  setName(cpy.getName());
  _id = cpy.getId();
  return *this;
}

bool	Utilities::Resource::operator==(Resource const& cmp) {
  if (getId() == cmp.getId())
    return true;
  return false;
}

uint32 Utilities::Resource::getId() const {
  return _id;
}

Utilities::ByteArray const&	Utilities::Resource::getFile() const {
  return _file;
}

void	Utilities::Resource::setArray(ByteArray const& cpy) {
  _file = cpy;
}

void	Utilities::Resource::readFile() {
  std::ifstream	ifs(_name.c_str(), std::ios::binary);
  char*		buffer;
  uint32		fileSize;

  ifs.seekg(0, std::ios::end);
  fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  buffer = new char[fileSize];
  ifs.read(buffer, fileSize);
  ifs.close();
  _file.bufcopy(buffer, fileSize);
  _file.debug();

  ByteArray	toto("loool", 5);
  _file.append(toto);
  _file.debug();
}
