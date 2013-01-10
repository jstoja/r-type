#ifndef IMENU_DELEGATE_H
# define IMENU_DELEGATE_H

namespace Menu {

  class IMenuDelegate {

    public:
      virtual ~IMenuDelegate() {}

      virtual void loginCompleted() = 0; 

      virtual void MapCompleted() = 0; 
      virtual void MapNotCompleted() = 0; 
  };
}

#endif
