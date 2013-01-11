//
// Application.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:09 2012 Samuel Olivier
//

#include <unistd.h>
#include "OS.h"
#include "Application.h"
#include "Exception.h"
#include "Debug.h"

Application::Application() :
_argv(NULL), _argc(0), _binaryPath(), _resourcesPath() {
}

Application::~Application() {
}

void Application::init(int32 ac, char **av) {
    _argc = ac;
    _argv = av;
    _getBinaryPath();
}

#ifndef OS_IOS

void Application::_getBinaryPath(void) {
# if defined OS_WINDOWS
    _binaryPath = av[0];
    _binaryPath = _binaryPath.substr(0, _binaryPath.find_last_of('\\'));
    _binaryPath += '\\';
# endif
# if (defined OS_UNIX)
    if (!(_argc > 0 && strlen(_argv[0]) > 0))
        throw new Exception("Application cannot find the binary directory");
    std::cout << "The _argv[0] has value: " << _argv[0] << std::endl;
    std::string cmd = _argv[0];
    if (cmd[0] == '/') {
        // If the binary has been launched from the root, we have the full path
        _binaryPath = cmd;
    } else if (cmd.find('/') != std::string::npos) {
        // Else, use getcwd and the path of launch to get the binary path
        char* cwd = getcwd(NULL, 4096);
        if (!cwd)
            throw new Exception("Application cannot get current working directory");
            _binaryPath = std::string(cwd) + "/" + cmd;
            free(cwd);
            } else
    throw new Exception("Application cannot be launched from a PATH, the "
                        "binary path, either absolute or relative to current"
                        " directory, must be in the launch command in order"
                        " to find the full binary path");

    // Remove the binary name from the path
    _binaryPath = cmd.substr(0, cmd.find_last_of('/'));
    _binaryPath += '/';
# endif
}

#endif


std::string Application::getResourcesPath() const {
    return _binaryPath + _resourcesPath + "/";
}

void Application::setRelativeResourcesPath(std::string const& path) {
    _resourcesPath = path;
}
