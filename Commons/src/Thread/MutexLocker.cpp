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
