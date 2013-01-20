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
# include "HostAddress.h"

namespace Network {

  class COMMON_EXPORT_IMPORT_REMOVED UdpPacket : public APacket {
  public:
    UdpPacket();
    virtual ~UdpPacket();

    void    read(ASocket*);
    void    update();
    bool    isComplete() const;

    void    setCode(uint32 code);
	void	setFrom(const HostAddress& hostAddress=HostAddress::AnyAddress, uint16 port=0);
    uint32  getCode();
    void    setId(uint32 code);
    uint32  getId();
    void    generateId(void);
    HostAddress getAddress() const;
    uint16	getPort() const;

    static bool	getHeaderInfos(ByteArray const& data, uint32& code);

  private:
    uint32  _id;
    HostAddress _hostAddress;
    uint16 _port;
  };

}

#endif
