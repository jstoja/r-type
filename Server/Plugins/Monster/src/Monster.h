//
// Monster.h for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#ifndef _MONSTER_H_
# define _MONSTER_H_

# include "IPlugin.h"

# include <IGame.h>
# include <IGraphicElement.h>
# include <IPhysicElement.h>
# include <IViewport.h>

class Monster: public IPlugin {
public:
    Monster(std::string const& pluginName);
	virtual ~Monster();
    
	virtual bool	init(IGame* game, ByteArray const& params, float32 xStart);
	virtual void	update();
	virtual float32	getXStart() const;
	virtual std::string const&	getName() const;
    
private:
    std::string         _name;
    IGame*				_game;
    float32             _xStart;
    float32             _speed;
    
    IGraphicElement*    _graphicElement;
    IPhysicElement*     _physicElement;
};

#endif