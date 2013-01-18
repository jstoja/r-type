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
# include "ByteArray.h"

namespace Network {

  class COMMON_EXPORT_IMPORT_REMOVED UdpPacket : public APacket {
  public:
    UdpPacket();
    virtual ~UdpPacket();

    void    read(ASocket*);
    void    update();
    bool    isComplete() const;

    void    setCode(uint32 code);
    uint32  getCode();

	static bool	getHeaderInfos(ByteArray const& data, uint32& code);
  };

}

#endif
