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

class Resource : public Object {
    public:
    
        //! Constructor
        COMMON_EXPORT_IMPORT inline Resource();

        //! Constructor with name
        COMMON_EXPORT_IMPORT inline Resource(std::string const&);
    
        //! Copy constructor
        COMMON_EXPORT_IMPORT inline Resource(Resource const&);

        //! Destructor
        COMMON_EXPORT_IMPORT inline ~Resource();
    
        //! Assignation operator
        COMMON_EXPORT_IMPORT inline Resource&	operator=(Resource const&);
    
        //! Comparaison operator
        COMMON_EXPORT_IMPORT inline bool		operator==(Resource const&);
    
        //! Name getter
        COMMON_EXPORT_IMPORT inline std::string const& getName() const;

        //! Name setter
        COMMON_EXPORT_IMPORT inline void	setName(std::string const&);

        //! File getter
        COMMON_EXPORT_IMPORT inline ByteArray const&	getData() const;

        //! Array setter
        COMMON_EXPORT_IMPORT inline void	setData(ByteArray const&);

    private:
        //! Read file and put in into a ByteArray
        COMMON_EXPORT_IMPORT inline void	_readFile();

        ByteArray	_data;
        std::string	_name;
};

#endif
