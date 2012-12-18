#ifndef _MUTEX_H_
# define _MUTEX_H_

# if defined (_WIN32)
#  include <windows.h>
# elif (defined __unix || defined __APPLE__)

# endif

namespace Threading {

	//! Mutex Class
	/*!  
		Provide a cross-platform class to use mutex
	*/
	class Mutex {
	public:

		//! Constructor
		/*!
			Create the mutex in a unlocked state
		*/
		Mutex();

		//! Destructor
		/*!
			Destroys the mutex.

			Warning: Destroying a locked mutex may result in undefined behavior.
		*/
		virtual ~Mutex();

		//! Lock the mutex
		/*!
			Locks the mutex. If another thread has locked the mutex then this call will block until that thread has unlocked it.
		*/
		void lock();
		//! Unlock the mutex
		/*!
			Unlock the mutex, and permit another thread to lock the mutex
		*/
		void unlock();

		//! Try to lock the mutex
		/*!
			Attempts to lock the mutex. If the lock was obtained, this function returns true. If another thread has locked the mutex, this function returns false immediately.
		
			If the lock was obtained, the mutex must be unlocked with unlock() before another thread can successfully lock it.
		*/
		bool tryLock();

	private:
# if defined (_WIN32)
		HANDLE	_mutex;
# elif (defined __unix || defined __APPLE__)
		pthreat_mutex_t _mutex;
# endif
	};
}

#endif