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

  TcpServer();
  ~TcpServer();

  void		setDelegate(ITcpServerDelegate*);
  bool		listen(const HostAddress& address = HostAddress::AnyAddress, uint16 port = 0);
  uint16	getLocalPort() const;

  void	newConnection(ASocket*);
  void	readFinished(ASocket*, Utilities::ByteArray&, const HostAddress&, uint16) {}
  void	dataReceived(ASocket*, Utilities::ByteArray&, uint32) {}
  void	dataSent(ASocket*, Utilities::ByteArray&, uint32) {}
  void	writeFinished(ASocket*, Utilities::ByteArray&) {}
  void	disconnection(ASocket*) {}

 private:
  TcpSocket		_socket;
  ITcpServerDelegate*	_delegate;
};

}

#endif
