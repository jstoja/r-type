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
    
    template <class T>
    class Proxy;

  template <typename T>
  class COMMON_EXPORT_IMPORT_REMOVED IProxyDelegate {
  public:
    virtual ~IProxyDelegate(void) {}
    virtual void packetReceived(T*) = 0;
    virtual void packetSent(T const*) = 0;
    virtual void connectionClosed(Network::Proxy<T>*) = 0;
  };

}

#endif
