#ifndef _RESSOURCE_H_
# define _RESSOURCE_H_

# include <iostream>

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
    int	getId() const;

  private:
    int		_id;
    std::string	_name;
  };

}

#endif
