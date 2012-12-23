/*
** APacket.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 09:02:01 2012 loick michard
*/

#ifndef _APACKET_H_
# define _APACKET_H_

# include <string>
# include "ByteArray.h"
# include "ASocket.h"
# include "HostAddress.h"

namespace Network {

  class APacket {
  public:
    APacket();
    ~APacket();

    virtual ByteArray&	getData();
    uint32		getSize() const;

    virtual void	read(ASocket*) = 0;
    virtual void	update() = 0;
    virtual bool	isComplete() const = 0;


    APacket&		operator<<(uint32);
    APacket&		operator<<(const std::string&);
    APacket&		operator>>(uint32&);
    APacket&		operator>>(std::string&);

  protected:
    ByteArray	_data;
    uint32      _size;
    uint32	_curser;
  };

}

#endif
