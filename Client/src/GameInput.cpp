//
// GameInput.cpp for R-Type in /home/olivie_a/R-Type
//
// Made by Samuel Olivier
// Login   <olivie_a@epitech.net>
// 
// Started on  dim. janv. 20 18:44:32 2013 Samuel Olivier
//

#include <Debug.h>

#include "GameInput.h"

template <> GameInput*	Singleton<GameInput>::_instance = new GameInput();

# ifndef OS_IOS

GameInput::GameInput() {
	_keys[Event::ArrowUp] = false;
	_keys[Event::ArrowDown] = false;
	_keys[Event::ArrowLeft] = false;
	_keys[Event::ArrowRight] = false;
	_listener = new Event::Listener(Event::KeyPressed | Event::KeyReleased, this);
}

GameInput::~GameInput() {
	disable();
	_listener->deleteLater();
}

void GameInput::processEvent(Event::Event const& event) {
	if (event.type == Event::KeyPressed || event.type == Event::KeyReleased) {
		_keys[(Event::Key)event.value] = (event.type == Event::KeyPressed);
		if (event.type == Event::KeyPressed && event.value == Event::ArrowUp)
			_keys[Event::ArrowDown] = false;
		else if (event.type == Event::KeyPressed && event.value == Event::ArrowDown)
			_keys[Event::ArrowUp] = false;
		else if (event.type == Event::KeyPressed && event.value == Event::ArrowLeft)
			_keys[Event::ArrowRight] = false;
		else if (event.type == Event::KeyPressed && event.value == Event::ArrowRight)
			_keys[Event::ArrowLeft] = false;
		_direction.x = _keys[Event::ArrowLeft] ? -1 : (_keys[Event::ArrowRight] ? 1 : 0);
		_direction.y = _keys[Event::ArrowUp] ? 1 : (_keys[Event::ArrowDown] ? -1 : 0);
		_direction.normalize();
	}
}

void GameInput::enable(void) {
    Event::Manager::getInstance().addEventListener(_listener);
}

void GameInput::disable(void) {
    Event::Manager::getInstance().removeEventListener(_listener);
}

# endif

Vec2 const&	GameInput::getInputDirection() const {
	return (_direction);
}

void GameInput::setInputDirection(Vec2 const& value) {
    _direction = value;
}