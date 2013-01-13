//
// LibraryFactory.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 12:43:40 2013 Samuel Olivier
//

#include <OS.h>
#include <Application.h>
#include "LibraryFactory.h"

LibraryFactory::LibraryFactory() {
}

LibraryFactory::~LibraryFactory() {
	clear();
}

Library* LibraryFactory::load(std::string const& dir, std::string const& name) {
	std::string key = dir + Application::getInstance().getDirectorySeparator();

#if defined(OS_WINDOWS)
	key += name + ".dll";
#elif defined (OS_MAC)
	key += "lib" + name + ".dylib";
#else
	key += "lib" + name + ".so";
#endif
	Library	*lib = _libraries[key];
	if (lib == NULL) {
		lib = new Library(key);
		if (lib->load() == false) {
			delete lib;
			return (NULL);
		}
		_libraries[key] = lib;
	}
	return lib;
}

void	LibraryFactory::clear() {
	for (std::map<std::string, Library*>::iterator it = _libraries.begin(); it != _libraries.end();) {
		delete it->second;
		it = _libraries.erase(it);
	}
}