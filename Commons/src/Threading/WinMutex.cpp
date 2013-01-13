//
// WinMutex.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:19:05 2012 Samuel Olivier
//

#include "../OS.h"

#if defined (OS_WINDOWS)
# include "Mutex.h"

Threading::Mutex::Mutex() {
	::InitializeCriticalSection(&_mutex);
}

Threading::Mutex::~Mutex(void) {
	::DeleteCriticalSection(&_mutex);
}

void Threading::Mutex::lock() {
	::EnterCriticalSection(&_mutex);
}

void Threading::Mutex::unlock() {
	::LeaveCriticalSection(&_mutex);
}

/*bool Threading::Mutex::tryLock() {
	//DWORD ret = WaitForSingleObject(_mutex, 0);
	//if (ret == WAIT_TIMEOUT)
		//return (false);
	return (TryLock(&_mutex));
}*/

Threading::Mutex::Condition::Condition(Mutex* mutex) :
	_mutex(mutex) {
	_cond = new CONDITION_VARIABLE;
	InitializeConditionVariable(_cond);
}

Threading::Mutex::Condition::~Condition() {
	delete _cond;
}

void Threading::Mutex::Condition::signal() {
	WakeConditionVariable(_cond);
}

void Threading::Mutex::Condition::wait() {
	SleepConditionVariableCS(_cond, &(_mutex->_mutex), INFINITE);
}

#endif
