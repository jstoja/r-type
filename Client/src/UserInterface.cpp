//
//  UserInterface.cpp
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include <sstream>
#include "UserInterface.h"
#include "Menu/GameJoin.h"
#include "Graphic/Image.h"
#include "Threading/MutexLocker.h"

const float32 UserInterface::_maxViewportX = 1000000000.0;

UserInterface::UserInterface(IUserInterfaceDelegate* delegate) :
_delegate(delegate), _time(), _eventListener(NULL), _sceneries(), _currentMenu(NULL),
_nextMenu(NULL), _messageLabel(NULL), _mutex(new Threading::Mutex()) {
    // Create the sceneries used in all the user interface
    _createSceneries();
    
	Menu::GameList*	menu = new Menu::GameList(_delegate->getScene(), this, "Server of the death");

	Menu::GamePrepare*	menu2 = new Menu::GamePrepare(_delegate->getScene(), this, "Server of the death", "Auto generated game", 3, 4);

	Menu::GameJoin*	menu3 = new Menu::GameJoin(_delegate->getScene(), this, "Server of the death", "The Game");
    
	_menus["Welcome"] = new Menu::Welcome(_delegate->getScene(), this);
	_menus["Login"] = new Menu::Login(_delegate->getScene(), this);
	_menus["Game"] = menu;
	_menus["NewGame"] = new Menu::NewGame(_delegate->getScene(), this, "Server Of The Death");
	_menus["GamePrepare"] = menu2;
	_menus["GameJoin"] = menu3;
    
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		it->second->setVisible(false);
    _currentMenu = _menus["Welcome"];
	_currentMenu->setVisible(true);
    
    _eventListener = new Event::Listener(Event::Close, this);
    Event::Manager::getInstance().addEventListener(_eventListener);
}

UserInterface::~UserInterface(void) {
	for (std::map<std::string, Menu::Menu*>::iterator it = _menus.begin(); it != _menus.end(); ++it)
		delete it->second;
	for (std::vector<Graphic::Scenery*>::iterator it = _sceneries.begin(); it != _sceneries.end(); ++it) {
        _delegate->getScene()->removeScenery(*it);
		delete *it;
    }
    
    delete _eventListener;
}

void UserInterface::update(void) {
    Threading::MutexLocker lock(_mutex);
    
    // Update the background (make it move !)
    float32 xPos = (float32)_time.getEllapsedTime() / 1000;
    if (xPos > _maxViewportX)
        xPos = 0;
    _delegate->getScene()->setViewportPosition(Vec2(xPos, 0));

    // Switch menu if requested
    if (_nextMenu) {
        _currentMenu->setVisible(false);
        _currentMenu = _nextMenu;
        _currentMenu->setVisible(true);
    }
}

void UserInterface::presentMessage(std::string const& message) {
    Threading::MutexLocker lock(_mutex);
    _messageLabel = new Widget::Label(_delegate->getScene());
    _messageLabel->setText(message);
    _messageLabel->setPosition(Vec3(_delegate->getScene()->getViewport().x,
                                    _delegate->getScene()->getViewport().y)
                               /2);
    _messageLabel->setSize(Vec2(_delegate->getScene()->getViewport().x, 0.6));
}

void UserInterface::hideMessage(void) {
    Threading::MutexLocker lock(_mutex);
    if (_messageLabel)
        delete _messageLabel;
}

Menu::Menu* UserInterface::getCurrentMenu(void) const {
    Threading::MutexLocker lock(_mutex);
    return _currentMenu;
}

void UserInterface::processEvent(Event::Event const &event) {
    Threading::MutexLocker lock(_mutex);
    if (event.type & Event::Close) {
        exit(EXIT_SUCCESS);
    }
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
    std::stringstream str;
    str << "CREATING GAME " << name << " WITH " << nbPlayers << " PLAYERS...";
	_currentMenu->setVisible(false);
    presentMessage(str.str());
}

void UserInterface::createGame() {
    goToMenu("NewGame");
}

void UserInterface::joinGame(uint32 idx) {
    std::stringstream str;
    str << "GAME " << idx;
    goToMenu("GameJoin");
}

void UserInterface::previous() {
    Menu::Menu* current = getCurrentMenu();
	if (current == _menus["Game"]) {
        goToMenu("Login");
	} else if (current == _menus["NewGame"]
               || current == _menus["GameJoin"]
               || current == _menus["GamePrepare"]) {
		goToMenu("Game");
	}
}

void UserInterface::playerReady(void) {
    
}

void UserInterface::goToMenu(std::string const& menu) {
    Threading::MutexLocker lock(_mutex);
    _nextMenu = _menus[menu];
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

void	UserInterface::setGameList(std::list<Game*> const& list) {
	Menu::GameList* menu = dynamic_cast<Menu::GameList*>(_menus["GameList"]);

	if (menu)
		menu->setGameList(list);
}

void	UserInterface::setPlayerList(std::list<Player*> const& list) {
	Menu::GamePrepare* menu = dynamic_cast<Menu::GamePrepare*>(_menus["GamePrepare"]);

	if (menu)
		menu->setPlayerList(list);
}
