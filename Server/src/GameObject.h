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

class IPlugin;
class IGame;

class GameObject {
public:
	GameObject(std::string const& name);
	~GameObject();
	
	void	init(IGame* game, ByteArray const& params);
	void	update();
private:
	IPlugin*	_plugin;
};

#endif
