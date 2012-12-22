//
// MutexLocker.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:18:42 2012 Samuel Olivier
//

#include "MutexLocker.h"

Threading::MutexLocker::MutexLocker(Mutex *mutex) : _mutex(mutex) {
	if (_mutex)
		_mutex->lock();
}


Threading::MutexLocker::~MutexLocker(void) {
	if (_mutex)
		_mutex->unlock();
}

Threading::Mutex*	Threading::MutexLocker::getMutex() const {
	return (_mutex);
}

void Threading::MutexLocker::relock() {
	if (_mutex != NULL)
		_mutex->lock();
}

void Threading::MutexLocker::unlock() {
	if (_mutex != NULL)
		_mutex->unlock();
}
