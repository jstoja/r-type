//
//  DLLoader.h
//  R-Type
//
//  Created by Franck Lavisse on 09/01/13.
//
//

#ifndef __R_Type__DLLoader__
# define __R_Type__DLLoader__

# include <iostream>
# include <string>

# include <OS.h>
# ifdef OS_WINDOWS
#  include <windows.h>
# else
#  include <dlfcn.h>
# endif

class DLLoader {
public:
    DLLoader(std::string& fileName);
    ~DLLoader();
    std::string const& getErrorString() const;
    std::string const& getFileName() const;
    bool	isLoaded() const;
    bool	load();
    void*	resolve(const char *);
    void	setFileName(std::string&);
    bool	unload();
private:
    std::string&    _fileName;
    bool    _load;
#ifdef OS_WINDOWS
    HMODULE  _handle;
#else
    void*   _handle;
#endif
    std::string     _errorString;
};

#endif /* defined(__R_Type__DLLoader__) */
