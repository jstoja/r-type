//
// Resource.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:16 2012 Samuel Olivier
//

#ifndef _RESSOURCE_H_
# define _RESSOURCE_H_

# include <iostream>
# include "Types.h"
# include "ByteArray.h"

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
    //! File getter
    ByteArray const&	getFile() const;
    //! ID getter
    uint32 getId() const;

  private:
    //! Read file and put in into a ByteArray
    void	readFile();
    //! Array setter
    void	setArray(ByteArray const&);

    ByteArray	_file;
    uint32		_id;
    std::string	_name;
  };

}

#endif
