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

 //   template <typename T>
 //   UdpPacket&		operator<<(std::list<T*>const& elements) {
	//	std::list<T*>::const_iterator it;

	//	*static_cast<ASocket*>(this) << elements.size();
	//	for (it = elements.begin(); it != elements.end(); ++it) {
	//		*static_cast<ASocket*>(this) << *(*it);
	//	}
	//	return (*this);
	//}

 //   template <typename T>
 //   UdpPacket&		operator<<(std::list<T> const& elements) {
	//	std::list<T>::const_iterator it;

	//	*static_cast<ASocket*>(this) << elements.size();
	//	for (it = elements.begin(); it != elements.end(); ++it) {
	//	  *static_cast<ASocket*>(this) << (*it);
	//	}
	//	return (*this);
	//}
	//
	//template <typename T>
 //   UdpPacket&		operator>>(std::list<T*>& elements) {
	//	uint32 size;

	//	*this >> size;
	//	for (uint32 i = 0; i < size; ++i) {
	//	  T* element = new T;
	//	  *this >> *element;
	//	  elements.push_front(element);
	//	}
	//}
 //   
	//template <typename T>
 //   UdpPacket&		operator>>(std::list<T>& elements) {
	//	uint32 size;

	//	*this >> size;
	//	for (uint32 i = 0; i < size; ++i) {
	//	  T element;
	//	  *this >> element;
	//	  elements.push_front(element);
	//	}  
	//}
  };

}

#endif
