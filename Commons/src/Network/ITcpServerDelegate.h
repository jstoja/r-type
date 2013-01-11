/*
** ITcpServerDelegate.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Thu Dec 20 16:35:54 2012 loick michard
*/

#ifndef _ITCP_SERVER_DELEGATE_H_
# define _ITCP_SERVER_DELEGATE_H_

# include <OS.h>

namespace Network {
  
  class COMMON_EXPORT_IMPORT ITcpServerDelegate {
  public:
    virtual void newConnection(ASocket*) = 0;
  };

}

#endif
