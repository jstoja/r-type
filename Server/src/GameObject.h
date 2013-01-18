//
// GameObject.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  sam. janv. 12 14:54:36 2013 Samuel Olivier
//

#ifndef _GAME_OBJECT_H_
# define _GAME_OBJECT_H_

# include <string>

# include <ByteArray.h>
# include <Object.h>
# include <Types.h>
# include "Threading/Mutex.h"
# include "Threading/MutexLocker.h"

class IPlugin;
class IGame;

class GameObject : public Object{
public:
	GameObject(std::string const& name);
	virtual ~GameObject();
	
	bool	init(IGame* game, ByteArray const& params, float32 xStart);
	void	update(void *params);
	float32	getXStart() const;

private:
	void                _loadPlugin();

	std::string         _pluginName;

    Threading::Mutex	*_pluginMutex;
	IPlugin*            _plugin;
};

#endif
