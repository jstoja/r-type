//
//  DLLoader.cpp
//  R-Type
//
//  Created by Franck Lavisse on 09/01/13.
//
//

#include "DLLoader.h"

DLLoader::DLLoader(std::string& fileName) : _fileName(fileName),
    _load(false), _handle(NULL) {
}

DLLoader::~DLLoader() {
    unload();
}

std::string const& DLLoader::getErrorString() const {
    return _errorString;
}

std::string const& DLLoader::getFileName() const {
    return _fileName;
}

bool	DLLoader::isLoaded() const {
    return _load;
}

bool	DLLoader::load() {
    _load = false;
    if ((_handle = dlopen(_fileName.c_str(), RTLD_LAZY)) == NULL)
        _errorString = dlerror();
    else
        _load = true;
    return _load;
}

void*	DLLoader::resolve(const char *name) {
    if (isLoaded()) {
        void *ptr = dlsym(_handle, name);
        if (ptr == NULL) {
            _errorString = dlerror();
            return NULL;
        }
        return ptr;
    }
    return NULL;
}

void	DLLoader::setFileName(std::string& filename) {
    _fileName = filename;
}

bool	DLLoader::unload() {
    if (_load) {
        dlclose(_handle);
        return true;
    }
    return false;
}