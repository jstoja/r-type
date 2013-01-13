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

# include <list>
# include <string>
# include <Vec2.h>
# include <Vec3.h>
# include <Rect2.h>
# include "ByteArray.h"
# include "ASocket.h"
# include "HostAddress.h"

namespace Network {

  class COMMON_EXPORT_IMPORT APacket {
  public:
    APacket();
    ~APacket();

    virtual ByteArray&	getData();
    uint32		getSize() const;

    virtual void	read(ASocket*) = 0;
    virtual void	update() = 0;
    virtual bool	isComplete() const = 0;


    APacket&		operator<<(uint32);
    APacket&		operator<<(float32);
    APacket&		operator<<(char);
    APacket&		operator<<(const std::string&);
    APacket&		operator<<(Vec2 const&);
    APacket&		operator<<(Vec3 const&);
    APacket&		operator<<(Rect2 const&);

    template <typename T>
    APacket&		operator<<(std::list<T*>const& elements) {
		typename std::list<T*>::const_iterator it;

		*this << (uint32)elements.size();
		for (it = elements.begin(); it != elements.end(); ++it) {
			*this << *(*it);
		}
		return (*this);
	}

    template <typename T>
    APacket&		operator<<(std::list<T> const& elements) {
		typename std::list<T>::const_iterator it;

		*this << (uint32)elements.size();
		for (it = elements.begin(); it != elements.end(); ++it) {
		  *this << (*it);
		}
		return (*this);
	}
    APacket&		operator>>(uint32&);
    APacket&		operator>>(float32&);
    APacket&		operator>>(char&);
    APacket&		operator>>(std::string&);

	template <typename T>
    APacket&		operator>>(std::list<T*>& elements) {
		uint32 size;

		*this >> size;
		for (uint32 i = 0; i < size; ++i) {
		  T* element = new T;
		  *this >> *element;
		  elements.push_front(element);
		}
	}
    
	template <typename T>
    APacket&		operator>>(std::list<T>& elements) {
		uint32 size;

		*this >> size;
		for (uint32 i = 0; i < size; ++i) {
		  T element;
		  *this >> element;
		  elements.push_front(element);
		}  
	}
    APacket&		operator>>(Vec2&);
    APacket&		operator>>(Vec3&);
    APacket&		operator>>(Rect2&);

  protected:
    ByteArray	_data;
    uint32      _size;
    uint32	_curser;
  };

}

#endif
