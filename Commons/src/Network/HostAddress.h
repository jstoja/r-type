/*
** HostAddress.h for r-type in /home/michar_l//r-type/Commons/src/Network
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Tue Dec 18 15:42:12 2012 loick michard
*/

#ifndef _HOST_ADDRESS_H_
# define _HOST_ADDRESS_H_

# include <string>
# include "Types.h"

namespace Network {

class COMMON_EXPORT_IMPORT HostAddress {
 public:
  static HostAddress AnyAddress;
  
  HostAddress(const std::string&);
  HostAddress(uint32 address);

  uint32	toIPv4Address() const;
  std::string	getString() const;

  bool operator==(const HostAddress&) const;
 private:
  uint32	_address;
};

}

#endif
