//
// LibraryFactory.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 12:41:58 2013 Samuel Olivier
//


#ifndef _LIBRARY_FACTORY_
# define _LIBRARY_FACTORY_

# include <map>

# include <Library.h>
# include <Singleton.hpp>

class COMMON_EXPORT_IMPORT LibraryFactory : public Singleton<LibraryFactory> {
    friend class Singleton<LibraryFactory>;
public:
    ~LibraryFactory();

	Library*	load(std::string const& dir, std::string const& name);
	void		clear();
private:
    LibraryFactory();

	std::map<std::string, Library*>     *_libraries;
};

#endif
