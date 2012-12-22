//
// ISocketDelegate.h for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 19:34:12 2012 loick michard
//

#ifndef _ISOCKET_DELEGATE_H_
# define _ISOCKET_DELEGATE_H_

# include "Utilities/ByteArray.h"
# include "HostAddress.h"

namespace Network {

class ASocket;

class ISocketDelegate {
 public:
  virtual void newConnection(ASocket*) = 0;
  virtual void readFinished(ASocket*, Utilities::ByteArray&, const HostAddress& hostAddress, uint16 port) = 0;
  virtual void dataReceived(ASocket*, Utilities::ByteArray&, uint32) = 0;
  virtual void dataSent(ASocket*, Utilities::ByteArray&, uint32) = 0;
  virtual void writeFinished(ASocket*, Utilities::ByteArray&) = 0;
  virtual void disconnection(ASocket*) = 0;
};

}

#endif
