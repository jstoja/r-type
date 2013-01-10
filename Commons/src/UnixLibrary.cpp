//
//  UnixLibrary.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include <OS.h>

#ifndef OS_WINDOWS

# include "Library.h"

bool	Library::load() {
    _load = false;
    if ((_handle = dlopen(_fileName.c_str(), RTLD_LAZY)) == NULL)
        _errorString = dlerror();
    else
        _load = true;
    return _load;
}

void*	Library::resolve(const char *name) {
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

void	Library::setFileName(std::string& filename) {
    _fileName = filename;
}

bool	Library::unload() {
    if (_load) {
        dlclose(_handle);
        return true;
    }
    return false;
}

#endif