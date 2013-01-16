//
// ITableDelegate.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. janv. 16 11:50:34 2013 Samuel Olivier
//

#ifndef _I_TABLE_DELEGATE_H_
# define _I_TABLE_DELEGATE_H_

# include <Types.h>

namespace Widget {
  class Table;

  class ITableDelegate {
    
    public:
      virtual ~ITableDelegate() {}

	  virtual void linePushed(Table* instance, uint32 line) {};
  };
}

#endif
