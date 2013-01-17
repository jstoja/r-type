/*
** TcpPacket.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 10:43:52 2012 loick michard
*/

#ifndef _TCP_PACKET_H_
# define _TCP_PACKET_H_

# include "APacket.h"

namespace Network {

  class COMMON_EXPORT_IMPORT TcpPacket : public APacket {
  public:
    TcpPacket();
    virtual ~TcpPacket();

    void	read(ASocket*);
    void	update();
    bool        isComplete() const;

    void	setCode(uint32 code);
    uint32     	getCode();      

  private:
    enum State {
      Empty,
      Header,
      Complete,
    };

    State	_state;
  };

}

#endif
