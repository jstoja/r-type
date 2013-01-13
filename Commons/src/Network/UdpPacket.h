/*
** UdpPacket.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 10:43:52 2012 loick michard
*/

#ifndef _UDP_PACKET_H_
# define _UDP_PACKET_H_

# include "APacket.h"

namespace Network {

  class COMMON_EXPORT_IMPORT_REMOVED UdpPacket : public APacket {
  public:
    UdpPacket();
    ~UdpPacket();

    void	read(ASocket*);
    void	update();
    bool    isComplete() const;
  };

}

#endif
