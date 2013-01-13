//
// Mutex.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:32 2012 Samuel Olivier
//

#ifndef _MUTEX_H_
# define _MUTEX_H_

# include <OS.h>

# if defined (OS_WINDOWS)
#  include <windows.h>
# elif defined (OS_UNIX)
#  include <pthread.h>
# endif

namespace Threading {

	//! Mutex Class
	/*!  
		Provide a cross-platform class to use mutex
	*/
	class COMMON_EXPORT_IMPORT Mutex {
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
# if defined (OS_WINDOWS)
		HANDLE	_mutex;
# elif defined (OS_UNIX)
		pthread_mutex_t *_mutex;
# endif
	};
}

#endif
