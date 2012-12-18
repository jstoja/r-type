#ifndef _RESSOURCE_H_
# define _RESSOURCE_H_

# include <iostream>
# include "Types.h"

namespace Utilities {
  class Resource {
  public:
    //! Constructor
    Resource();
    //! Constructor with name
    Resource(std::string const&);	   
    //! Copy constructor
    Resource(Resource const&);
    //! Destructor
    ~Resource();
    
    //! Assignation operator
    Resource&	operator=(Resource const&);
    //! Comparaison operator
    bool		operator==(Resource const&);
    
    //! Name getter
    std::string const& getName() const;
    //! Name setter
    void	setName(std::string const&);
    //! ID getter
    uint32 getId() const;

  private:
    uint32		_id;
    std::string	_name;
  };

}

#endif
