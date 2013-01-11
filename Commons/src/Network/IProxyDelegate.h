/*
** IProxyDelegate.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 10:37:58 2012 loick michard
*/

#ifndef _IPROXY_DELEGATE_H_
# define _IPROXY_DELEGATE_H_

# include <OS.h>

namespace Network {

  template <typename T>
  class COMMON_EXPORT_IMPORT_REMOVED IProxyDelegate {
  public:
    virtual ~IProxyDelegate() {}
    virtual void newPacket(T*) = 0;
    virtual void packetWrited(T*) = 0;
  };

}

#endif
