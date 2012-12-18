#ifndef _UNIX_THREAD_HPP_
# define _UNIX_THREAD_HPP_

# include "../OS.h"

# if defined (OS_UNIX)

#  include <pthread.h>

namespace Threading {

	template<class T>
	static void	*_unixThreadCallback(void *obj)
	{
		T	*newObj = static_cast<T*>(obj);
		if (newObj)
			(*newObj)();
		return (0);
	}

	//! Unix Thread Class Implementation
	/*!  
		Provide an implementation of the AThread class for the Unix Operating System
	*/
	template<class T>
	class Thread
	{
	public:
		//! Constructor
		/*!  
			Construct the thread and save the object that will be used to launch the thread
		*/
		Thread(T *obj) : _obj(obj), _thread(NULL) {
		}

		//! Destructor
		/*!
			Destroys the thread.

			Note that deleting a Thread object will not stop the execution of the thread it represents. Deleting a running Thread will probably result in a program crash. You can join() on a thread to make sure that it has finished.
		*/
		~Thread(void) {
		}

		//! Launch the thread
		/*!  
			Launch the thread by calling the operator() of the object given in the constructor
		*/
		void run(void) {
			if (_thread == NULL)
				pthread_create(&_thread, NULL, _unixThreadCallback<T>, _obj);
		}

		//! Wait for the thread
		/*!  
			Wait for the thread end
		*/
		void join(void) {
			pthread_join(_thread, NULL);
		}

	private:
		T*			_obj;
		pthread_t	_thread;
	};
};

# endif

#endif