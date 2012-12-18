#if (defined __unix || defined __APPLE__)

# include <unistd.h>
# include "Mutex.h"

Threading::Mutex::Mutex() {
	pthread_mutex_init(&_mutex, NULL);
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
