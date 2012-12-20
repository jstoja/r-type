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
//! Construct the object
Application();
//! Destruct the object
~Application();

//! Init with argc/argv of main
void init(char **, int32);

//! Get the resources path
std::string const&	getResourcesPath() const;

//! Contact path for resources
void	concatPath();

private:
char**		_av;
int32		_ac;
std::string	_resourcesPath;
};

#endif
