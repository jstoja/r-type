//
// ASocket.h for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 19:20:41 2012 loick michard
//

#ifndef _ASOCKET_H_
# define _ASOCKET_H_

# include "ISocketDelegate.h"
# include "HostAddress.h"
# include "ByteArray.h"

namespace Network {
  
  class ASocket {
  public:
    ASocket();
    ~ASocket();

    bool	isListening() const;
    bool	isReading() const;
    bool	isWriting() const;
    void	setDelegate(ISocketDelegate*);

    virtual void	read(ByteArray&, bool all = true, uint32 start = 0) = 0;
    virtual void	write(ByteArray&, const HostAddress& hostAddress = HostAddress::AnyAddress, uint16 port = 0) = 0;
    virtual void       	close() = 0;
    virtual int		getId() const = 0;
    virtual void	canRead() = 0;
    virtual void	canWrite() = 0;
    virtual uint16	getLocalPort() const = 0;
    
  protected:
    bool		_reading;
    bool		_listening;
    bool		_writing;
    ISocketDelegate*	_delegate;
  };

}

#endif
