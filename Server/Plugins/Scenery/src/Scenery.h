//
// Scenery.h for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#ifndef _SCENERY_H_
# define _SCENERY_H_

# include "IPlugin.h"
# include "IScenery.h"
# include "IGame.h"

class IGraphicElement;
class IPhysicElement;

class Scenery: public IPlugin {
public:
    Scenery(std::string const& pluginName);
    virtual ~Scenery();
    
    virtual bool                init(IGame* game, ByteArray const& params, float32 xStart);
	virtual void                update();
	virtual float32             getXStart() const;
	virtual std::string const&	getName() const;
    
private:
    //Plugin
  	IGame*				_game;
	std::string			_name;
    IScenery*           _scenery;
};

#endif