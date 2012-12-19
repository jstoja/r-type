//
// Atomic.hpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  mer. déc. 19 12:20:45 2012 Samuel Olivier
//

#ifndef _ATOMIC_HPP_
# define _ATOMIC_HPP_

# include "Mutex.h"

namespace Threading {
	//! Thread Safe Container 
	/*!  
		Provide a Thread Safe Scalar Container
	*/
	template<class T>
	class Atomic {
	public:
		//! Constructor
		/*!
			Construct the object and call the default constructor of the T object 
		*/
		Atomic() {
		}

		//! Destructor
		/*!
			Destruct the object
		*/
		~Atomic() {
		}


		//! Assign
		/*!
			Assign a new value to the one stored in the object
		*/
		T& operator=(T const& other) {
			_mutex.lock();
			_obj = other;
			_mutex.unlock();
			return (_obj);
		}

		//! Get the value
		/*!
			Return the value stored in the object
		*/
		operator T() const {
			return (_obj);
		}

	private:
		T		_obj;
		Mutex	_mutex;
	};
}

#endif