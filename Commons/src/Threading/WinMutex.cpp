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
