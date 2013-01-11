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
# include "Singleton.hpp"
# include "ASocket.h"
# include "Threading/Thread.h"
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

namespace Network {
  
	class COMMON_EXPORT_IMPORT NetworkManager : public Singleton<NetworkManager> {
    
    friend class Singleton<NetworkManager>;
    friend class Threading::Thread<NetworkManager>;
    
	public:
		void	registerSocket(ASocket*);
		void	unregisterSocket(ASocket*);

		void	operator()();

	private:

		NetworkManager();
		~NetworkManager();

		std::vector<ASocket*>			_sockets;
		Threading::Mutex				_socketsMutex;
		Threading::Thread<NetworkManager>		_runThread;
	};

}

#endif
