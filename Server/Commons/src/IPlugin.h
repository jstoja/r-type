//
// IPlugin.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 16:05:34 2013 Samuel Olivier
//

#ifndef _I_PLUGIN_H_
# define _I_PLUGIN_H_

# include <OS.h>
# include <ByteArray.h>

# ifdef OS_WINDOWS
#  define PLUGIN_EXPORT __declspec(dllexport)
# else
#  define PLUGIN_EXPORT
# endif

# define RTYPE_PLUGIN_PARAMS std::string const& name
# define RTYPE_PLUGIN_CREATE extern "C" PLUGIN_EXPORT IPlugin	*newPlugin(RTYPE_PLUGIN_PARAMS)

class IGame;

class IPlugin {
public:
	typedef IPlugin	*(*CreatorPrototype)(RTYPE_PLUGIN_PARAMS);
	virtual ~IPlugin() {}

	virtual bool	init(IGame* game, ByteArray const& params, float32 xStart) = 0;
	virtual void	update() = 0;
	virtual float32	getXStart() const = 0;
	virtual std::string const&	getName() const = 0;
};

#endif