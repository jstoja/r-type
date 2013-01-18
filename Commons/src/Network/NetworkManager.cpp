//
// NetworkManager.cpp for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 21:45:15 2012 loick michard
//

#include <iostream>
#include "OS.h"
#ifdef OS_WINDOWS
# include <winsock2.h>
# define usleep(x) Sleep((x) / 1000)
#else
# include <unistd.h>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
#endif
#include "NetworkManager.h"

# ifndef OS_IOS
template <> Network::NetworkManager* Singleton<Network::NetworkManager>::_instance = new Network::NetworkManager();
# endif

Network::NetworkManager::NetworkManager() : _runThread(this) {
#ifdef OS_WINDOWS
     WSADATA wsa;
     WSAStartup (MAKEWORD (2,2), &wsa);
#endif
    _sockets = new std::vector<ASocket*>;
    _runThread.run();
}

Network::NetworkManager::~NetworkManager() {

}

void Network::NetworkManager::registerSocket(Network::ASocket* socket) {
  Threading::MutexLocker locker(&_socketsMutex);
  _sockets->push_back(socket);
}

void Network::NetworkManager::unregisterSocket(Network::ASocket* socket) {
  Threading::MutexLocker locker(&_socketsMutex);
  std::vector<ASocket*>::iterator it;
  for (it = _sockets->begin(); it != _sockets->end();)
    if (*it == socket)
      it = _sockets->erase(it);
    else
      ++it;
}

void Network::NetworkManager::operator()() {
  fd_set		readSockets;
  fd_set		writeSockets;
  int			max;
  struct timeval	tv;

  while (1) {
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    FD_ZERO(&readSockets);
    FD_ZERO(&writeSockets);
    max = -1;

    _socketsMutex.lock();
    std::vector<ASocket*>::iterator it;

    for (it = _sockets->begin(); it != _sockets->end(); ++it) {
      if ((*it)->isReading() || (*it)->isListening()) {
	FD_SET((*it)->getId(), &readSockets);
	if ((*it)->getId() >= max)
	  max = (*it)->getId() + 1;
      }
      if ((*it)->isWriting()) {
      	FD_SET((*it)->getId(), &writeSockets);
      	if ((*it)->getId() >= max)
      	  max = (*it)->getId() + 1;
      }
    }
    _socketsMutex.unlock();
    if (max != -1) {
      int ret = select(max, &readSockets, &writeSockets, NULL, &tv);
      if (ret == -1)
	; // Throw an error
      else {
	_socketsMutex.lock();
	
	unsigned int size = _sockets->size();
	for (unsigned int i = 0; i < size; ++i) {
	  if ((_sockets->at(i)->isReading() || _sockets->at(i)->isListening()) && FD_ISSET(_sockets->at(i)->getId(), &readSockets)) {
	    _socketsMutex.unlock();
	    _sockets->at(i)->canRead();
	    _socketsMutex.lock();
	  }
        // Crappy patch, if the socket is deleted during canRead()
        if (_sockets->size() < size) {
            size = _sockets->size();
            --i;
        } else if (_sockets->size() < size) {
            size = _sockets->size();
        } else if (_sockets->at(i)->isWriting() && FD_ISSET(_sockets->at(i)->getId(), &writeSockets)) {
	    _socketsMutex.unlock();
	    _sockets->at(i)->canWrite();
	    _socketsMutex.lock();
	  }
	}
	_socketsMutex.unlock();
      }
    } else
      usleep(100000);
  }
}
