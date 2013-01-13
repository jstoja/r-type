/*
** TcpServer.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Tue Dec 18 15:29:20 2012 loick michard
*/

#ifndef _TCP_SERVER_H_
# define _TCP_SERVER_H_

# include "TcpSocket.h"
# include "HostAddress.h"
# include "Types.h"
# include "ISocketDelegate.h"
# include "ITcpServerDelegate.h"

namespace Network {

  class TcpServer : public ISocketDelegate {
 public:

  COMMON_EXPORT_IMPORT inline TcpServer();
  COMMON_EXPORT_IMPORT inline ~TcpServer();

  COMMON_EXPORT_IMPORT inline void		setDelegate(ITcpServerDelegate*);
  COMMON_EXPORT_IMPORT inline bool		listen(const HostAddress& address = HostAddress::AnyAddress, uint16 port = 0);
  COMMON_EXPORT_IMPORT inline uint16	getLocalPort() const;

  COMMON_EXPORT_IMPORT inline void	newConnection(ASocket*);
  COMMON_EXPORT_IMPORT inline void	readFinished(ASocket*, ByteArray&, const HostAddress&, uint16) {}
  COMMON_EXPORT_IMPORT inline void	dataReceived(ASocket*, ByteArray&, uint32) {}
  COMMON_EXPORT_IMPORT inline void	dataSent(ASocket*, ByteArray&, uint32) {}
  COMMON_EXPORT_IMPORT inline void	writeFinished(ASocket*, ByteArray&) {}
  COMMON_EXPORT_IMPORT inline void	disconnection(ASocket*) {}

 private:
  TcpSocket		_socket;
  ITcpServerDelegate*	_delegate;
};

}

#endif
