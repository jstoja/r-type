#ifndef _APPLICATION_H_
# define _APPLICATION_H_

# include "Types.h"
# include "Singleton.hpp"

namespace Utilities {

  class Application : public Singleton<Application> {
    friend class Singleton<Application>;

  public:
    //! Construct the object
    Application();
    //! Destruct the object
    ~Application();

    //! Init with argc/argv of main
    void init(char **, int32);

  private:
    char	**_av;
    int32	    _ac;
  };

};

#endif
