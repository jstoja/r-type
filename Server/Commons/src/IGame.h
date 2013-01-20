//
// IGame.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  jeu. janv. 10 10:40:05 2013 Samuel Olivier
//

#ifndef _I_GAME_H_
# define _I_GAME_H_

# include <string>

class IGraphicElement;
class ITexture;
class ISprite;
class IPhysicElement;
class ISound;
class IScenery;
class IViewport;

class IGame {
public:
	~IGame() {}

	virtual void				addGraphicElement(IGraphicElement* element) = 0;
	virtual IGraphicElement*	createGraphicElement() const = 0;
	virtual ITexture*			createTexture(std::string const& filename,
                                              std::string const& pluginName="") = 0;
	virtual ISprite*			createSprite(ITexture *texture) = 0;
	virtual ISprite*			getLevelSprite(std::string const& name) = 0;

	virtual void				addPhysicElement(IPhysicElement* element) = 0;
	virtual IPhysicElement*		createPhysicElement() const = 0;

	virtual ISound*				loadSound(std::string const& name, std::string const& pluginName) = 0;
	virtual ISound*				loadSound(std::string const& name) = 0;

	virtual IScenery*			addScenery() = 0;
	virtual IViewport*			getViewport() const = 0;
    
    virtual uint64              getEllapsedTime() const = 0;
};

#endif