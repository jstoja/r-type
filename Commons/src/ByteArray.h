#ifndef _BYTE_ARRAY_H_
# define _BYTE_ARRAY_H_

# include <iostream>
# include <string>
# include <vector>
# include "Types.h"

class COMMON_EXPORT_IMPORT ByteArray {
    public:
        //! Constructor
        ByteArray();
    
        //! Construct with size only
        ByteArray(uint32);
    
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
        std::vector<char> const& getBuffer() const;

        //! Size getter
        uint32		getSize() const;
    
        //! Append ByteArray
        void		append(ByteArray const&);

        //! Append char * / uint32
        void		append(char *, uint32);

        //! Copy buffer with char * + size
        void		bufcopy(const char *, uint32);
    
        //! Copy vector
        void		bufcopy(std::vector<char> const&);

        //! Get char buffer
        char const*       getData() const;
    
        // Return pointer to buffer data
        operator char*();
    
        operator const char*() const;
    
        void        resize(uint32);
    
        void		debug() const;
  private:
        std::vector<char>	_buffer;
};

#endif
