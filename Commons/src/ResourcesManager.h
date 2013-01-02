//
// ResourcesManager.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:12 2012 Samuel Olivier
//

#ifndef _RESSOURCESMANAGER_H_
# define _RESSOURCESMANAGER_H_

# include <map>
# include <string>
# include "Singleton.hpp"

class Resource;

class ResourcesManager : public Singleton<ResourcesManager> {
    friend class Singleton<ResourcesManager>;

    public:
        //! Destructor
        ~ResourcesManager();
    
        //! Load a resource and return a pointer to it
        Resource* loadResource(std::string const&);

        //! Remove resource from map
        void removeResource(std::string const&);

        //! Get a resource by name
        Resource*	getResource(std::string const&);

        //! Get a resource by id
        Resource*	getResource(uint32) const;

    private:
        //! Constructor
        ResourcesManager();
    
        std::map<uint32, Resource*>		_resourcesId;
        std::map<std::string, Resource*>	_resourcesName;
};

#endif
