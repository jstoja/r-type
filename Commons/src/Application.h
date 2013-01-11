//
// Application.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:54 2012 Samuel Olivier
//

#ifndef _APPLICATION_H_
# define _APPLICATION_H_

# include <iostream>
# include <string>
# include "Types.h"
# include "Singleton.hpp"

class Application : public Singleton<Application> {
    friend class Singleton<Application>;

    public:
    
    //! Destruct the object
    ~Application();

    //! Init with argc/argv of main
    /*!
     At init, the Application will find full path of its binary in order to
     locate its resources later.
     */
    void init(int32 ac, char **av);

    //! Get the resources path
    std::string getResourcesPath() const;

    // Set the resources path, relative to the binary
    void        setRelativeResourcesPath(std::string const& path);

    private:
    //! Construct the object
    Application();
    
    void _getBinaryPath(void);

    char**		_argv;
    int32		_argc;
    std::string	_binaryPath;
    std::string	_resourcesPath;
};

#endif
