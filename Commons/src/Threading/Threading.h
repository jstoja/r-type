#ifndef _THREADING_H_
# define _THREADING_H_

# include "Mutex.h"
# include "Thread.h"
# include "Atomic.hpp"
# include "MutexLocker.h"

/*!
 *  \addtogroup Threading
 *  @{
 */
//! Cross-Platform Thread implementation and utils
/*!
	The cross-platform threading namespace contains:
		Threads implementation
		Mutex implementation
		Mutex utils like Atomic and MutexLocker class
*/
namespace Threading {
	template<class T>
	class Thread;

	class Mutex;

	class MutexLocker;

	template<class T>
	class Atomic;
}
/*! @} End of Doxygen Groups*/

#endif