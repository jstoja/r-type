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
# include "Object.h"

class COMMON_EXPORT_IMPORT Resource : public Object {
    public:
    
        //! Constructor
        Resource();

        //! Constructor with name
        Resource(std::string const&, bool generateId = true);
    
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
        ByteArray const&	getData() const;

        //! Array setter
        void	setData(ByteArray const&);

    private:
        //! Read file and put in into a ByteArray
        void	_readFile();

        ByteArray	_data;
        std::string	*_name;
};

#endif
