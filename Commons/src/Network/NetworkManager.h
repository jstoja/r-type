//
// NetworkManager.h for r-type in /home/michar_l//r-type
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Mon Dec 17 19:38:38 2012 loick michard
//

#ifndef _NETWORK_MANAGER_H_
# define _NETWORK_MANAGER_H_

# include <vector>

# include <OS.h>
# include <Singleton.hpp>

# include "ASocket.h"
# include "Threading/Thread.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"
namespace Network {
  
	class NetworkManager : public Singleton<NetworkManager> {
    
    friend class Singleton<NetworkManager>;
    friend class Threading::Thread<NetworkManager>;
    
	public:
		COMMON_EXPORT_IMPORT inline void	registerSocket(ASocket*);
		COMMON_EXPORT_IMPORT inline void	unregisterSocket(ASocket*);

		COMMON_EXPORT_IMPORT inline void	operator()();

	private:

		COMMON_EXPORT_IMPORT inline NetworkManager();
		COMMON_EXPORT_IMPORT inline ~NetworkManager();

		std::vector<ASocket*>			_sockets;
		Threading::Mutex				_socketsMutex;
		Threading::Thread<NetworkManager>		_runThread;
	};

}

#endif
