//
// UnixMutex.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:26 2012 Samuel Olivier
//

#include "../OS.h"

#if defined (OS_UNIX)

# include "Mutex.h"
# include <unistd.h>

Threading::Mutex::Mutex() {
	_mutex = new pthread_mutex_t;
	pthread_mutex_init(_mutex, NULL);
}

Threading::Mutex::~Mutex(void) {
	pthread_mutex_destroy(_mutex);
}

void Threading::Mutex::lock() {
	pthread_mutex_lock(_mutex);
}

void Threading::Mutex::unlock() {
	pthread_mutex_unlock(_mutex);
}

/*bool Threading::Mutex::tryLock() {
	return pthread_mutex_trylock(_mutex);
}*/

Threading::Mutex::Condition::Condition(Mutex* mutex) :
  _mutex(mutex) {
  _cond = new pthread_cond_t;
  pthread_cond_init(_cond, NULL);
}

Threading::Mutex::Condition::~Condition() {
  delete _cond;
}

void Threading::Mutex::Condition::signal() {
  pthread_cond_signal(_cond);
}

void Threading::Mutex::Condition::wait() {
  pthread_cond_wait(_cond, _mutex->_mutex);
}

#endif
