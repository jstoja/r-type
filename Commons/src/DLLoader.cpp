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
#ifdef OS_WINDOWS
    _handle = LoadLibrary(TEXT(_fileName.c_str()));
#else
    if ((_handle = dlopen(_fileName.c_str(), RTLD_LAZY)) == NULL)
        _errorString = dlerror();
    else
        _load = true;
#endif
    return _load;
}

void*	DLLoader::resolve(const char *name) {
    if (isLoaded()) {
#ifdef OS_WINDOWS
        void *ptr = GetProcAddress(_handle, name);
#else
        void *ptr = dlsym(_handle, name);
        if (ptr == NULL) {
            _errorString = dlerror();
            return NULL;
        }
#endif
        return ptr;
    }
    return NULL;
}

void	DLLoader::setFileName(std::string& filename) {
    _fileName = filename;
}

bool	DLLoader::unload() {
    if (_load) {
#ifdef OS_WINDOWS
        FreeLibrary(_handle);
#else
        dlclose(_handle);
#endif
        return true;
    }
    return false;
}