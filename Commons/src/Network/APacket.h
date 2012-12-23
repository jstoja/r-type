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

# include "ByteArray.h"

namespace Network {

  class APacket {
  public:
    APacket();
    ~APacket();

    ByteArray&	getData();
  protected:
    ByteArray	_data;
  };

}

#endif
