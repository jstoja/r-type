//
//  WinLibrary.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include <OS.h>

#ifdef OS_WINDOWS

#include "Library.h"

bool	Library::load() {
    _load = false;
    _handle = LoadLibrary(TEXT(_fileName.c_str()));
    return _load;
}

void*	Library::resolve(const char *name) {
    if (isLoaded()) {
        void *ptr = GetProcAddress(_handle, name);
        return ptr;
    }
    return NULL;
}

void	Library::setFileName(std::string& filename) {
    _fileName = filename;
}

bool	Library::unload() {
    if (_load) {
        FreeLibrary(_handle);
        return true;
    }
    return false;
}

#endif