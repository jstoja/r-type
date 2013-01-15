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
#include "Exception.h"
#include "ResourcesManager.h"

Resource::Resource() : Object() {
    _name = new std::string();
}

Resource::Resource(std::string const& name) : Object() {
    _name = new std::string(name);
    _readFile();
}

Resource::~Resource() {
	ResourcesManager::getInstance().removeResource(getName());
	delete _name;
}

Resource::Resource(Resource const& cpy) : Object(cpy.getId()) {
    setName(cpy.getName());
    setData(cpy.getData());
}

std::string const& Resource::getName() const {
    return *_name;
}

void	Resource::setName(std::string const& name) {
	delete _name;
    _name = new std::string(name);
}

Resource&	Resource::operator=(Resource const& cpy) {
    setName(cpy.getName());
    setId(cpy.getId());
    return *this;
}

bool	Resource::operator==(Resource const& cmp) {
    if (getId() == cmp.getId())
        return true;
    return false;
}

ByteArray const& Resource::getData() const {
    return _data;
}

void Resource::setData(ByteArray const& cpy) {
    _data = cpy;
}

void	Resource::_readFile() {
	std::string filename = App.getResourcesPath() + App.convertPath(*_name);
    std::ifstream   ifs(filename.c_str(), std::ios::binary);
    uint32          fileSize;

    if (!ifs.is_open()) {
        throw new Exception("Cannot open resource file: " + filename);
    }
    ifs.seekg(0, std::ios::end);
    fileSize = (uint32)ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    _data.resize(fileSize);
    ifs.read((char*)_data, fileSize);
    ifs.close();
}
