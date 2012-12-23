/*
** Client.h for r-type in /home/michar_l//r-type/Server/src
** 
** Made by loick michard
** Login   <michar_l@epitech.net>
** 
** Started on  Sun Dec 23 09:34:24 2012 loick michard
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#include "Network/ASocket.h"

class Client {
 public:
  Client(Network::ASocket*);
  ~Client();

 private:
  Network::ASocket*	_socket;
};

#endif
