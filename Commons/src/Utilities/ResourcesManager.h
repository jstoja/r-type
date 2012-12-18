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
    void addResource(std::string const&, Resource *);
    //! Remove resource from map
    void removeResource(std::string const&);
    
    //! Get a resource
    Resource*	getResource(std::string const& name);
  private:
    std::map<std::string, Resource*>	_resources;
  };

}

#endif
