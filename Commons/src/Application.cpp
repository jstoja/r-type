//
// Application.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
//
// Started on  mer. déc. 19 12:19:09 2012 Samuel Olivier
//

#include "OS.h"
#ifndef OS_WINDOWS
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
#endif
#include "Application.h"
#include "Exception.h"
#include "Debug.h"

#ifndef OS_IOS
template <> Application* Singleton<Application>::_instance = new Application();
#endif

Application::Application() :
_argv(NULL), _argc(0), _binaryPath(new std::string("")), _resourcesPath(new std::string("")) {
}

Application::~Application() {
	delete _binaryPath;
	delete _resourcesPath;
}

void Application::init(int32 ac, char **av) {
    _argc = ac;
    _argv = av;
	_initBinaryPath();
}

#ifndef OS_IOS
void	Application::_initBinaryPath() {
# if defined OS_WINDOWS
    *_binaryPath = _argv[0];
    *_binaryPath = _binaryPath->substr(0, _binaryPath->find_last_of('\\'));
    *_binaryPath += '\\';
# elif defined (OS_UNIX)
    if (!(_argc > 0 && strlen(_argv[0]) > 0))
        throw new Exception("Application cannot find the binary directory");
    std::string cmd = _argv[0];
    if (cmd[0] == '/') {
        // If the binary has been launched from the root, we have the full path
        *_binaryPath = cmd;
    } else if (cmd.find('/') != std::string::npos) {
        // Else, use getcwd and the path of launch to get the binary path
        char* cwd = getcwd(NULL, 4096);
        if (!cwd)
            throw new Exception("Application cannot get current working directory");
        *_binaryPath = std::string(std::string(cwd) + std::string("/") + cmd);
        free(cwd);
    } else
        throw new Exception("Application cannot be launched from a PATH, the "
                            "binary path, either absolute or relative to current"
                            " directory, must be in the launch command in order"
                            " to find the full binary path");

    // Remove the binary name from the path
    *_binaryPath = cmd.substr(0, cmd.find_last_of('/'));
    *_binaryPath += '/';
# endif
}
#endif

std::string Application::getRelativePath(std::string const& path) const {
	std::string tmp = *_binaryPath + convertPath(path);
	return (tmp);
}
	
std::string Application::getResourcesPath() const {
    return *_binaryPath + *_resourcesPath + getDirectorySeparator();
}

void Application::setRelativeResourcesPath(std::string const& path) {
    *_resourcesPath = convertPath(path);
}

char Application::getDirectorySeparator() const {
# if defined OS_WINDOWS
	return ('\\');
# else
	return ('/');
#endif
}

std::string	Application::convertPath(std::string const& path) const {
	std::string filename = path;
	if (getDirectorySeparator() != '/') {
		size_t	idx;
		while ((idx = filename.find_last_of('/')) != std::string::npos) {
			filename.replace(idx, 1, 1, Application::getInstance().getDirectorySeparator());
		}
	}
	return (filename);
}