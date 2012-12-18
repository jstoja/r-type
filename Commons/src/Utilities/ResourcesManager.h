#ifndef _RESSOURCESMANAGER_H_
# define _RESSOURCESMANAGER_H_

#include <map>

namespace Utilities {

  class Resource;

  class ResourcesManager {
  public:
    //! Constructor
    ResourcesManager();
    //! Destructor
    ~ResourcesManager();
    
    //! Add resource in map
    void addResource(Resource *);
    //! Load a resource and return a pointer to it
    Resource* loadResource(std::string const&);
    //! Remove resource from map
    void removeResource(std::string const&);
    
    //! Get a resource by name
    Resource*	getResource(std::string const&);
    //! Get a resource by id
    Resource*	getResource(uint32_t) const;
  private:
    std::map<uint32_t, Resource*>		_resourcesId;
    std::map<std::string, Resource*>	_resourcesName;
  };

}

#endif
