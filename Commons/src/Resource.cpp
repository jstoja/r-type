//
// Resource.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:37 2012 Samuel Olivier
//

#include <fstream>
#include "UUIDGenerator.h"
#include "Resource.h"
#include "Application.h"

Resource::Resource() {
}

Resource::Resource(std::string const& name) {  
    _name = name;
    _id = UUIDGenerator::getInstance().getUUID();
    readFile();
}

Resource::~Resource() {
}

Resource::Resource(Resource const& cpy) {
    setName(cpy.getName());
    _id = cpy.getId();
    setArray(cpy.getFile());
}

std::string const& Resource::getName() const {
    return _name;
}

void	Resource::setName(std::string const& name) {
    _name = name;
}

Resource&	Resource::operator=(Resource const& cpy) {
    setName(cpy.getName());
    _id = cpy.getId();
    return *this;
}

bool	Resource::operator==(Resource const& cmp) {
    if (getId() == cmp.getId())
        return true;
    return false;
}

uint32 Resource::getId() const {
    return _id;
}

ByteArray const& Resource::getFile() const {
    return _file;
}

void Resource::setArray(ByteArray const& cpy) {
    _file = cpy;
}

void	Resource::readFile() {
    std::ifstream	ifs(_name.c_str(), std::ios::binary);
    char*		buffer;
    uint32		fileSize;

    ifs.seekg(0, std::ios::end);
    fileSize = (uint32)ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    buffer = new char[fileSize];
    ifs.read(buffer, fileSize);
    ifs.close();
    _file.bufcopy(buffer, fileSize);
}
