//
//  WinLibrary.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include <OS.h>

#ifdef OS_WINDOWS

# include "Library.h"

bool	Library::load() {
	if (isLoaded() == false) {
		if ((_handle = LoadLibrary(TEXT(_fileName->c_str()))) == NULL)
			_errorString->assign(std::string("Cannot load library: ") + *_fileName);
		else
			_load = true;
	}
    return isLoaded();
}

void*	Library::resolve(const char *name) {
    if (isLoaded()) {
        void *ptr = GetProcAddress(_handle, name);
		if (ptr == NULL)
			_errorString->assign(std::string("Cannot resolve symbol: ") + std::string(name));
        return ptr;
    }
	_errorString->assign("Library is not loaded");
    return NULL;
}

bool	Library::unload() {
    if (isLoaded()) {
		if (FreeLibrary(_handle) == false) {
			_errorString->assign(std::string("Cannot unload library: ") + *_fileName);
			return (false);
		}
		else
			return (true);
	}
	_errorString->assign((char*)"Library is not loaded");
    return false;
}

#endif