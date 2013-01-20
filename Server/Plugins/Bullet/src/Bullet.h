//
// Bullet.h for R-Type in /home/bordel_/R-Type
//
// Made by Julien Bordellier
// Login   <bordel@epitech.net>
//
// Started on  Sam. janv. 19 13:48:32 2013 Julien Bordellier
//

#ifndef _BULLET_H_
# define _BULLET_H_

# include <IPlugin.h>
# include <IGame.h>
# include <IGraphicElement.h>
# include <IPhysicElement.h>
# include <IViewport.h>

class Bullet: public IPlugin {
public:
    Bullet(std::string const& pluginName);
	virtual ~Bullet();
    
	virtual bool	init(IGame* game, ByteArray const& params, float32 xStart);
	virtual void	update();
	virtual float32	getXStart() const;
	virtual std::string const&	getName() const;
    
private:
    std::string         _name;
    IGame*				_game;
    float32             _xStart;

    Vec2                _direction;
    float32             _speed;
    
    IGraphicElement*    _graphicElement;
    IPhysicElement *    _physicElement;
};

#endif