//
//  Library.cpp
//  R-Type
//
//  Created by Franck Lavisse on 09/01/13.
//
//

#include "Library.h"

Library::Library(std::string& fileName) :
	_fileName(new std::string(fileName)),
    _load(false),
	_handle(NULL),
	_errorString(new std::string()) {
}

Library::~Library() {
    unload();    
	delete _errorString;
	delete _fileName;
}

std::string const& Library::getErrorString() const {
    return *_errorString;
}

std::string const& Library::getFileName() const {
    return *_fileName;
}

bool	Library::isLoaded() const {
    return _load;
}

void	Library::setFileName(std::string& filename) {
    _fileName->assign(filename);
}