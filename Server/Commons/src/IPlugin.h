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

# ifdef OS_WINDOWS
#  define PLUGIN_EXPORT __declspec(dllexport)
# else
#  define PLUGIN_EXPORT
#endif

class IPlugin {
public:
	~IPlugin() {}

	virtual void	update() = 0;
};

#endif