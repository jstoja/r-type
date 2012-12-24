//
// HostAddress.cpp for r-type in /home/michar_l//r-type/Commons/src/Network
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue Dec 18 15:51:08 2012 loick michard
//

#include "OS.h"
#if defined(OS_WINDOWS)
# include <winsock2.h>
#else
# include <arpa/inet.h>
#endif
#include "HostAddress.h"

Network::HostAddress Network::HostAddress::AnyAddress = HostAddress(INADDR_ANY);

Network::HostAddress::HostAddress(const std::string& address) {
  _address = inet_addr(address.c_str());
}

Network::HostAddress::HostAddress(uint32 address) {
  _address = htonl(address);
}

uint32 Network::HostAddress::toIPv4Address() const {
  return _address;
}

std::string Network::HostAddress::getString() const {
  in_addr address;

  address.s_addr = _address;
  return std::string(inet_ntoa(address));
}
