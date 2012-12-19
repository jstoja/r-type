//
// WinThread.hpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:50 2012 Samuel Olivier
//

#ifndef _WIN_THREAD_HPP_
# define _WIN_THREAD_HPP_

# include "../OS.h"

# if defined (OS_WINDOWS)

#  include <windows.h>

namespace Threading {

	template<class T>
	static DWORD WINAPI	_winThreadCallback(LPVOID obj)
	{
		T	*newObj = static_cast<T*>(obj);
		if (newObj)
			(*newObj)();
		return (0);
	}

	//! Thread Class
	/*!  
		Provide a cross-platform class to use thread
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
				_thread = CreateThread(NULL, 0, _winThreadCallback<T>, _obj, 0, &_threadId);
		}

		//! Wait for the thread
		/*!  
			Wait for the thread end
		*/
		void join(void) {
			WaitForSingleObject(_thread, INFINITE);
		}

	private:
		T*		_obj;
		HANDLE	_thread;
		DWORD	_threadId;
	};
};

# endif

#endif
