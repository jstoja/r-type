/*
** UdpSocket.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Thu Dec 20 18:10:53 2012 loick michard
*/

#ifndef _UDP_SOCKET_H_
# define _UDP_SOCKET_H_

# include <iostream>
# include <cstring>
# include "OS.h"
# ifdef OS_WINDOWS
#  include <winsock2.h>
# else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <unistd.h>
# endif
# include "ASocket.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

namespace Network {
  
  class UdpSocket : public ASocket {
  public:
    const static uint32 readSize = 32768;
    const static uint32 writeSize = 2048;
    
    UdpSocket();
    UdpSocket(int fd);
    ~UdpSocket();

    int   getId() const;

    bool	bind(const HostAddress& address = HostAddress::AnyAddress, uint16 port = 0);
    void	read(ByteArray&, bool all = true, uint32 start = 0);
    void	write(ByteArray&, const HostAddress& hostAddress = HostAddress::AnyAddress, uint16 port = 0);
    void	close();

    void	canRead();
    void	canWrite();
    uint16	getLocalPort() const;

  private:
    int				_fd;

    ByteArray*			_readBuffer;
    Threading::Mutex		_readMutex;

    ByteArray*			_writeBuffer;
    Threading::Mutex		_writeMutex;
    HostAddress			_writeAddress;
    uint16			_writePort;
    uint32			_writePosition;
  };

}

#endif
