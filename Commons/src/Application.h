//
// Application.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. d�c. 19 12:20:54 2012 Samuel Olivier
//

#ifndef _APPLICATION_H_
# define _APPLICATION_H_

# include <iostream>
# include <string>
# include "Types.h"
# include "Singleton.hpp"

class COMMON_EXPORT_IMPORT_REMOVED Application : public Singleton<Application> {
    friend class Singleton<Application>;

    public:
    
        //! Destruct the object
        ~Application();

        //! Init with argc/argv of main
        void init(int32 ac, char **av);

        //! Get the resources path
        std::string getResourcesPath() const;
    
        // Set the resources path, relative to the binary
        void        setRelativeResourcesPath(std::string const& path);

    private:
        //! Construct the object
        Application();

		char**		_av;
        int32		_ac;
        std::string	_binaryPath;
        std::string	_resourcesPath;
};

#endif
