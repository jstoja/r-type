//
// GameInput.h for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 20 18:35:34 2013 Samuel Olivier
//

#ifndef _GAME_INPUT_H_
# define _GAME_INPUT_H_

# include <map>

# include <OS.h>
# include <Singleton.hpp>
# include <Vec2.h>
# include <Event/Manager.h>
# include <Event/Event.h>
# include <Event/IListenerDelegate.h>

# ifdef OS_IOS
class GameInput : public Singleton<GameInput> {
# else
class GameInput : public Singleton<GameInput>, public Event::IListenerDelegate {
# endif
	friend class Singleton<GameInput>;

public:
	virtual ~GameInput();

	Vec2 const&	getInputDirection() const;
    void        setInputDirection(Vec2 const& value);
# ifndef OS_IOS
	virtual void processEvent(Event::Event const& event);
# endif
    
    void enable(void);
    void disable(void);

private:
	GameInput();

# ifdef OS_IOS

# else
	Event::Listener*			_listener;
	std::map<Event::Key, bool>	_keys;
# endif
	Vec2						_direction;
};

#endif