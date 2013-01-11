//
// TcpSocket.hpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 19:25:14 2012 loick michard
//

#ifndef _TCP_SOCKET_HPP_
# define _TCP_SOCKET_HPP_

# include <string>
# include "NetworkManager.h"
# include "ASocket.h"
# include "HostAddress.h"
# include "Types.h"
# include "ByteArray.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

namespace Network {

  class COMMON_EXPORT_IMPORT TcpSocket : public ASocket  {

public:
    const static uint32 readSize = 4096;
    const static uint32 writeSize = 32768;

  TcpSocket();
  TcpSocket(int fd);
  ~TcpSocket();

  int	getId() const;

  bool		connect(const HostAddress& address, uint16 port);
  bool		listen(const HostAddress& address, uint16 port);
  void		read(ByteArray&, bool all = true, uint32 start = 0);
  void		write(ByteArray&, const HostAddress& hostAddress = HostAddress::AnyAddress, uint16 port = 0);
  void		close();
  uint16       	getLocalPort() const;

  void	canRead();
  void	canWrite();
  
private:
  int			_fd;
  HostAddress		_hostAddress;
  uint16		_hostPort;

  ByteArray		_buffer;
  Threading::Mutex	_bufferMutex;

  unsigned int		_toRead;
  ByteArray*		_bufferToRead;
  bool			_readAll;
  uint32		_readStart;
  Threading::Mutex	_bufferToReadMutex;

  ByteArray*		_bufferToWrite;
  uint32		_writePosition;
  Threading::Mutex	_bufferToWriteMutex;
};

}

#endif
