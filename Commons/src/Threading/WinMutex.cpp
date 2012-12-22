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

Threading::Mutex::Mutex() : _mutex(CreateMutex(NULL, FALSE, NULL)) {
}

Threading::Mutex::~Mutex(void) {
	CloseHandle(_mutex);
}

void Threading::Mutex::lock() {
	WaitForSingleObject(_mutex, INFINITE);
}

void Threading::Mutex::unlock() {
	ReleaseMutex(_mutex);
}

bool Threading::Mutex::tryLock() {
	DWORD ret = WaitForSingleObject(_mutex, 0);
	if (ret == WAIT_TIMEOUT)
		return (false);
	return (true);
}

#endif
