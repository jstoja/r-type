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
# include <OS.h>

class Resource;

class COMMON_EXPORT_IMPORT ResourcesManager : public Singleton<ResourcesManager> {
    friend class Singleton<ResourcesManager>;

    public:
        //! Destructor
        COMMON_EXPORT_IMPORT inline ~ResourcesManager();
    
        //! Load a resource and return a pointer to it
        COMMON_EXPORT_IMPORT inline Resource* loadResource(std::string const&);

        //! Remove resource from map
        COMMON_EXPORT_IMPORT inline void removeResource(std::string const&);

        //! Get a resource by name
        COMMON_EXPORT_IMPORT inline Resource*	getResource(std::string const&);

        //! Get a resource by id
        COMMON_EXPORT_IMPORT inline Resource*	getResource(uint32) const;

    private:
        //! Constructor
        COMMON_EXPORT_IMPORT inline ResourcesManager();
    
        std::map<uint32, Resource*>		_resourcesId;
        std::map<std::string, Resource*>	_resourcesName;
};

#endif
