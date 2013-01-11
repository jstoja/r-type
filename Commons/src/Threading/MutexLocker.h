//
// MutexLocker.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:27 2012 Samuel Olivier
//

#ifndef _MUTEX_LOCKER_H_
# define _MUTEX_LOCKER_H_

# include "Mutex.h"

namespace Threading {
	//! Mutex Wrapper
	/*!
		Mutex wrapper, locking and unlocking the mutex
	*/
	class COMMON_EXPORT_IMPORT MutexLocker {
	public:
		//! Constructor
		/*!
			Constructs a MutexLocker and locks the mutex. The mutex will be unlocked when the QMutexLocker is destroyed. If mutex is zero, MutexLocker does nothing.
		*/
		MutexLocker(Mutex *mutex);

		//! Destructor
		/*!
			Destroys the MutexLocker and unlocks the mutex that was locked in the constructor.
		*/
		virtual ~MutexLocker(void);

		//! Get the mutex
		/*!
			Returns a pointer to the mutex that was locked in the constructor.
		*/
		Mutex* getMutex() const;

		//! Relock the mutex
		/*!
			Relocks an unlocked mutex locker.
		*/
		void relock();

		//! Unlock the mutex
		/*!
			Unlocks this mutex locker. You can use relock() to lock it again. It does not need to be locked when destroyed.
		*/
		void unlock();

	private:
		Mutex* _mutex;
	};
}

#endif