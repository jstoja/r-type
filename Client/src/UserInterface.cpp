//
//  UserInterface.cpp
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include <sstream>
#include "Widget/Manager.h"
#include "UserInterface.h"
#include "Menu/GameJoin.h"
#include "Graphic/Image.h"
#include "Threading/MutexLocker.h"

const float32 UserInterface::_maxViewportX = 1000000000.0;

UserInterface::UserInterface(IUserInterfaceDelegate* delegate) :
_delegate(delegate), _time(), _sceneries(), _currentMenu(NULL),
	_messageLabel(NULL), _mutex(new Threading::Mutex()), _visible(true), _showLabel(false) {
    // Create the sceneries used in all the user interface
    _createSceneries();

    // Create all menus
	_menus["Welcome"] = new Menu::Welcome(_delegate->getScene(), this);
	_menus["Login"] = new Menu::Login(_delegate->getScene(), this);
	_menus["GameList"] = new Menu::GameList(_delegate->getScene(), this);
	_menus["NewGame"] = new Menu::NewGame(_delegate->getScene(), this);
	_menus["GamePrepare"] = new Menu::GamePrepare(_delegate->getScene(), this);
	_menus["GameJoin"] = new Menu::GameJoin(_delegate->getScene(), this);
    
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		it->second->setVisible(false);
    _currentMenu = _menus["Welcome"];
	_currentMenu->setVisible(true);
    
    // Create the message label
    _messageLabel = new Widget::Label(_delegate->getScene());
    _messageLabel->setPosition(Vec3(_delegate->getScene()->getViewport().x,
                                    _delegate->getScene()->getViewport().y)
                               /2);
    _messageLabel->setSize(Vec2(_delegate->getScene()->getViewport().x, 0.6));
    _messageLabel->setVisible(false);
}

UserInterface::~UserInterface(void) {
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		delete it->second;
	for (std::vector<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it) {
        _delegate->getScene()->removeScenery(*it);
		delete *it;
    }
}

void UserInterface::update(void) {
    Threading::MutexLocker lock(_mutex);

	if (_visible) {
		if (_currentMenu && _currentMenu->isVisible() && _showLabel)
			_currentMenu->setVisible(false);
		else if (_currentMenu && _currentMenu->isVisible() == false && _showLabel == false)
			_currentMenu->setVisible(true);
	}
    // Update the background (make it move !)
    float32 xPos = (float32)_time.getEllapsedTime() / 1000;
    if (xPos > _maxViewportX)
        xPos = 0;
    _delegate->getScene()->setViewportPosition(Vec2(xPos, 0));

    // Switch menu if requested
	Widget::Manager::getInstance().update();
}

void UserInterface::presentMessage(std::string const& message) {
    Threading::MutexLocker lock(_mutex);
	_showLabel = true;
    _messageLabel->setText(message);
    _messageLabel->setVisible(true);
}

void UserInterface::hideMessage(void) {
    Threading::MutexLocker lock(_mutex);
	_showLabel = false;
    if (_messageLabel->isVisible())
        _messageLabel->setVisible(false);
}

Menu::Menu* UserInterface::getCurrentMenu(void) const {
    Threading::MutexLocker lock(_mutex);
    return _currentMenu;
}

void UserInterface::welcomeCompleted(void) {
    // Present login menu
    goToMenu("Login");
}

void UserInterface::loginCompleted(std::string const& login,
								   std::string const& ipAdress,
								   std::string const& port) {
	_delegate->loginCompleted(login, ipAdress, port);
}

void UserInterface::newGameCompleted(std::string const& name,
                                     uint32 nbPlayers) {
    _delegate->newGameCompleted(name, nbPlayers);
}

void UserInterface::createGame() {
    goToMenu("NewGame");
}

void UserInterface::joinGame(uint32 idx) {
    _delegate->gameSelected(idx);
}

void UserInterface::previous() {
    Menu::Menu* current = getCurrentMenu();
	if (current == _menus["GameList"]) {
        _delegate->leavedGameList();
	} else if (current == _menus["NewGame"]) {
		goToMenu("GameList");
	} else if (current == _menus["GameJoin"]
               || current == _menus["GamePrepare"]) {
        _delegate->leavedGame();
    }
}

void UserInterface::playerReady(void) {
	_delegate->playerReady();
}

void UserInterface::goToMenu(std::string const& menu) {
    Threading::MutexLocker lock(_mutex);
    if (_currentMenu)
       _currentMenu->setVisible(false);
	_currentMenu = _menus[menu];
    if (_currentMenu)
       _currentMenu->setVisible(true);
	else
		_currentMenu = NULL;
}

void UserInterface::_createSceneries(void) {
    _sceneries.clear();
    
    Graphic::Image image;
    Graphic::Scenery* scenery;
    Graphic::Texture* texture;
     
    image.loadFromResource("background.png");
    texture = new Graphic::Texture();
    texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    scenery = new Graphic::Scenery();
    scenery->setTexture(texture);
    scenery->setRange(Vec2(0, 1000));
    scenery->setWidth(16);
    scenery->setSpeed(0);
    scenery->setDepth(0.999);
    _delegate->getScene()->addScenery(scenery);
    _sceneries.push_back(scenery);

    image.loadFromResource("stars-deep.png");
    texture = new Graphic::Texture();
    texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    scenery = new Graphic::Scenery();
    scenery->setTexture(texture);
    scenery->setRange(Vec2(0, 1000));
    scenery->setWidth(16);
    scenery->setSpeed(0.2);
    scenery->setDepth(0.998);
    scenery->setOpacity(0.2);
    _delegate->getScene()->addScenery(scenery);
    _sceneries.push_back(scenery);

    image.loadFromResource("stars-blue.png");
    texture = new Graphic::Texture();
    texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    scenery = new Graphic::Scenery();
    scenery->setTexture(texture);
    scenery->setRange(Vec2(0, 1000));
    scenery->setWidth(16);
    scenery->setSpeed(0.8);
    scenery->setDepth(0.997);
    _delegate->getScene()->addScenery(scenery);
    _sceneries.push_back(scenery);

    image.loadFromResource("stars-red.png");
    texture = new Graphic::Texture();
    texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    scenery = new Graphic::Scenery();
    scenery->setTexture(texture);
    scenery->setRange(Vec2(0, 1000));
    scenery->setWidth(16);
    scenery->setSpeed(1.2);
    scenery->setDepth(0.996);
    _delegate->getScene()->addScenery(scenery);
    _sceneries.push_back(scenery);

    image.loadFromResource("planets.png");
    texture = new Graphic::Texture();
    texture->setData(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    scenery = new Graphic::Scenery();
    scenery->setTexture(texture);
    scenery->setRange(Vec2(0, 1000));
    scenery->setWidth(3 * 16);
    scenery->setSpeed(0.5);
    scenery->setDepth(0.995);
    scenery->setOpacity(0.8);
    _delegate->getScene()->addScenery(scenery);
    _sceneries.push_back(scenery);
}

void	UserInterface::setServerName(std::string const& serverName) {
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		it->second->setServerName(serverName);
}

void	UserInterface::setGameName(std::string const& gameName) {
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		it->second->setGameName(gameName);
}

void	UserInterface::setGameList(std::list<Game*> const& list) {
	Menu::GameList* menu = dynamic_cast<Menu::GameList*>(_menus["GameList"]);

	if (menu)
		menu->setGameList(list);
}

void	UserInterface::setCurrentGame(Game* game) {
	Menu::GamePrepare* menu = dynamic_cast<Menu::GamePrepare*>(_menus["GamePrepare"]);

	if (menu)
		menu->setCurrentGame(game);
}

void	UserInterface::setVisible(bool visible) {
	if (visible == _visible)
		return ;
	_mutex->lock();
	_visible = visible;
	if (_visible == true) {
		for (std::vector<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it)
			_delegate->getScene()->addScenery(*it);
		for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
			it->second->setVisible(it->second == _currentMenu);
		_messageLabel->setVisible(false);
	} else {
		for (std::vector<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it)
			_delegate->getScene()->removeScenery(*it);
		for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
			it->second->setVisible(false);
		_messageLabel->setVisible(false);
	}
	_mutex->unlock();
}

void	UserInterface::setResourceProgress(float32 progress) {
	Menu::GameJoin* menu = dynamic_cast<Menu::GameJoin*>(_menus["GameJoin"]);

	if (menu)
		menu->setProgress(progress);

}
