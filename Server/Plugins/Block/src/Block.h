//
// Block.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 14:06:34 2013 Samuel Olivier
//


#ifndef _BLOCK_H_
# define _BLOCK_H_

# include <map>

# include <IPlugin.h>

class IGame;
class IGraphicElement;
class IPhysicElement;

class Block : public IPlugin {
public:
	Block(std::string const& pluginName);
	virtual ~Block();

	virtual bool	init(IGame* game, ByteArray const& params,
						float32 xStart);
	virtual void	update();
	virtual float32	getXStart() const;
	virtual std::string const&	getName() const;

private:
	enum Type {
		SHIP = 0,
	};

	IGame*				_game;
	IGraphicElement*	_block;
	float32				_xStart;
	IPhysicElement*		_physicElement;
	IGraphicElement*	_graphicElement;
	std::string			_name;
	static std::map<Type, std::string>	_images;
};

#endif