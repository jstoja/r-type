#ifndef _BYTE_ARRAY_H_
# define _BYTE_ARRAY_H_

# include <iostream>
# include <string>
# include "Types.h"

namespace Utilities {

  class	ByteArray {
  public:
    //! Constructor
    ByteArray();
    //! Constructor with buffer and size
    ByteArray(const char *,  uint32);
    //! Copy constructor
    ByteArray(ByteArray const&);
    //! Destructor
    ~ByteArray();
    
    //! Assignation
    ByteArray&	operator=(ByteArray const&);
    //! Comparaison
    bool		operator==(ByteArray const&);
    //! Comparaison
    bool		operator!=(ByteArray const&);  
    //! Append
    ByteArray&	operator<<(ByteArray const&);

    //! Buffer getter
    char*		getBuffer() const;
    //! Size getter
    uint32		getSize() const;
    //! Size setter
    void		setSize(uint32);
    //! Buffer and size setters
    void		setAll(const char *, uint32);
    //! Append ByteArray
    void		append(ByteArray const&);
    //! Append char * / uint32
    void		append(char *, uint32);
  private:
    char*		_buffer;
    uint32		_size;
  };

}

//! Show
std::ostream&	operator<<(std::ostream &os, Utilities::ByteArray const&);


#endif
