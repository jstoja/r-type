//
//  UnixLibrary.cpp
//  R-Type
//
//  Created by Franck Lavisse on 10/01/13.
//
//

#include <OS.h>

#ifdef OS_UNIX

# include "Library.h"

bool	Library::load() {
	if (isLoaded() == false) {
		_load = false;
		if ((_handle = dlopen(_fileName->c_str(), RTLD_LAZY)) == NULL)
			_errorString->assign(dlerror());
		else
			_load = true;
	}
    return isLoaded();
}

void*	Library::resolve(const char *name) {
    if (isLoaded()) {
        void *ptr = dlsym(_handle, name);
        if (ptr == NULL)
            _errorString->assign(dlerror());
        return ptr;
    }
	_errorString->assign("Library is not loaded");
    return NULL;
}

bool	Library::unload() {
    if (_load) {
        if (dlclose(_handle) == 0)
	       return true;
		else {
			_errorString->assign(dlerror());
			return false;
		}
    }
	_errorString->assign("Library is not loaded");
    return false;
}

#endif