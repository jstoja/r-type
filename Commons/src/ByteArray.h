#ifndef _BYTE_ARRAY_H_
# define _BYTE_ARRAY_H_

# include <iostream>
# include <string>
# include <vector>

# include "Types.h"

class ByteArray {
    public:
        //! Constructor
        COMMON_EXPORT_IMPORT inline ByteArray();
    
        //! Construct with size only
        COMMON_EXPORT_IMPORT inline ByteArray(uint32);
    
        //! Constructor with buffer and size
        COMMON_EXPORT_IMPORT inline ByteArray(const char *,  uint32);
    
        //! Copy constructor
        COMMON_EXPORT_IMPORT inline ByteArray(ByteArray const&);
    
        //! Destructor
        COMMON_EXPORT_IMPORT inline ~ByteArray();
    

        //! Assignation
        COMMON_EXPORT_IMPORT inline ByteArray&	operator=(ByteArray const&);

        //! Comparaison
        COMMON_EXPORT_IMPORT inline bool		operator==(ByteArray const&);

        //! Comparaison
        COMMON_EXPORT_IMPORT inline bool		operator!=(ByteArray const&);

        //! Append
        COMMON_EXPORT_IMPORT inline ByteArray&	operator<<(ByteArray const&);

        //! Buffer getter
        COMMON_EXPORT_IMPORT inline std::vector<char> const& getBuffer() const;

        //! Size getter
        COMMON_EXPORT_IMPORT inline uint32		getSize() const;
    
        //! Append ByteArray
        COMMON_EXPORT_IMPORT inline void		append(ByteArray const&);

        //! Append char * / uint32
        COMMON_EXPORT_IMPORT inline void		append(char *, uint32);

        //! Copy buffer with char * + size
        COMMON_EXPORT_IMPORT inline void		bufcopy(const char *, uint32);
    
        //! Copy vector
        COMMON_EXPORT_IMPORT inline void		bufcopy(std::vector<char> const&);

        //! Get char buffer
        COMMON_EXPORT_IMPORT inline char const*       getData() const;
    
        // Return pointer to buffer data
        COMMON_EXPORT_IMPORT inline operator char*();
    
        COMMON_EXPORT_IMPORT inline operator const char*() const;
    
        COMMON_EXPORT_IMPORT inline void        resize(uint32);
    
        COMMON_EXPORT_IMPORT inline void		debug() const;
  private:
        std::vector<char>	_buffer;
};

#endif
