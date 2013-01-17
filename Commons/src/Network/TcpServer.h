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

  class COMMON_EXPORT_IMPORT TcpServer : public ISocketDelegate {
 public:

  TcpServer();
  ~TcpServer();

  void		setDelegate(ITcpServerDelegate*);
  bool		listen(const HostAddress& address = HostAddress::AnyAddress, uint16 port = 4242);
  uint16	getLocalPort() const;

  void	newConnection(ASocket*);
  void	readFinished(ASocket*, ByteArray&, const HostAddress&, uint16) {}
  void	dataReceived(ASocket*, ByteArray&, uint32) {}
  void	dataSent(ASocket*, ByteArray const&, uint32) {}
  void	writeFinished(ASocket*, ByteArray const&) {}
  void	disconnection(ASocket*) {}

 private:
  TcpSocket             _socket;
  ITcpServerDelegate*	_delegate;
};

}

#endif
