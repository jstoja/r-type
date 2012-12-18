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
    
    //! Get a resource (and load if necessary)
    Resource*	getResource(std::string const& name);
  private:
    std::map<std::string, Resource*>	_resources;
  };

}

#endif
