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

  class TcpSocket : public ASocket  {

public:
    const static uint32 readSize = 4096;
    const static uint32 writeSize = 32768;

  COMMON_EXPORT_IMPORT inline TcpSocket();
  COMMON_EXPORT_IMPORT inline TcpSocket(int fd);
  COMMON_EXPORT_IMPORT inline ~TcpSocket();

  COMMON_EXPORT_IMPORT inline int	getId() const;

  COMMON_EXPORT_IMPORT inline bool		connect(const HostAddress& address, uint16 port);
  COMMON_EXPORT_IMPORT inline bool		listen(const HostAddress& address, uint16 port);
  COMMON_EXPORT_IMPORT inline void		read(ByteArray&, bool all = true, uint32 start = 0);
  COMMON_EXPORT_IMPORT inline void		write(ByteArray&, const HostAddress& hostAddress = HostAddress::AnyAddress, uint16 port = 0);
  COMMON_EXPORT_IMPORT inline void		close();
  COMMON_EXPORT_IMPORT inline uint16       	getLocalPort() const;

  COMMON_EXPORT_IMPORT inline void	canRead();
  COMMON_EXPORT_IMPORT inline void	canWrite();
  
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
