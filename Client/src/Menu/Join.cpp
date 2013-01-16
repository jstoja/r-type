//
//  Join.cpp
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include <sstream>

#include "Join.h"
#include "Graphic/Scene.h"

Menu::Join::Join(Graphic::Scene *scene, IMenuDelegate* delegate,
                std::string const& serverName) : Menu(scene, delegate) {
	std::string upperName = serverName;
    std::transform(serverName.begin(), serverName.end(), upperName.begin(), ::toupper);
    _serverNameLabel = new Widget::Label(scene, upperName);
    _serverNameLabel->setPosition(Vec3(scene->getViewport().x / 2, scene->getViewport().y - 0.8));
	_serverNameLabel->setSize(Vec2(scene->getViewport().x - (0.425 * 2), 0.50));
    _serverNameLabel->setTextAligment(Widget::Label::TextAlignRight);

	_previousMenu = new Widget::Button(scene, this, "button-left-arrow.png");
	_previousMenu->setSize(Vec2(0.56, 0.575));
	_previousMenu->setPosition(Vec3(_previousMenu->getSize().x / 2 + 0.425, scene->getViewport().y - 0.8));

	_gameList = new Widget::Table(2, "table-lines.png", scene, this);
	_gameList->setColumnAlignement(Widget::Table::Right, 1);
	std::vector<std::string> names;	
	names.push_back("GAMES NAME");
	names.push_back("PLAYER");
	_gameList->setHeaderNames(names);
	float x = scene->getViewport().x / 2, y = scene->getViewport().y - 4.6;
	_gameList->setPosition(Vec3(x, y));
	_nextPageButton = new Widget::Button(scene, this, "button-right-arrow.png");
	_nextPageButton->setSize(Vec2(0.56, 0.575));
	_nextPageButton->setPosition(Vec3(getScene()->getViewport().x - _nextPageButton->getSize().x / 2 - 0.425, y - _gameList->getSize().y / 2 - _nextPageButton->getSize().y / 2 - 0.25));
	_nextPageButton->getElement()->setVisible(false);
	_previousPageButton = new Widget::Button(scene, this, "button-left-arrow.png");
	_previousPageButton->setSize(Vec2(0.56, 0.575));
	_previousPageButton->setPosition(_nextPageButton->getPosition() - Vec3(_nextPageButton->getSize().x / 2 + _previousPageButton->getSize().x / 2, 0, 0));
	_previousPageButton->getElement()->setVisible(false);
	_createGame = new Widget::Button(scene, this, "button-new-game.png");
	_createGame->setSize(Vec2(3.45, 0.575));
	_createGame->setPosition(Vec3(_createGame->getSize().x / 2 + 0.425, y - _gameList->getSize().y / 2 - _createGame->getSize().y / 2 - 0.2));
}

Menu::Join::~Join(void) {
	delete _serverNameLabel;
	delete _gameList;
	delete _nextPageButton;
	delete _previousPageButton;
	delete _createGame;
}

void Menu::Join::addGame(std::string const& gameName, uint32 gamePlayerNumber, uint32 gamePlayerSlot) {
	std::stringstream tmp;
	tmp << gamePlayerNumber << "/" << gamePlayerSlot;
	std::vector<std::string>	line;
	line.push_back(gameName);
	line.push_back(tmp.str());
	uint32 idx = _gameList->addLine(line);
	if (gamePlayerNumber == gamePlayerSlot)
		_gameList->setColor(idx, Vec3(0x9999CF));
	_updatePageButtons();
}

void Menu::Join::buttonReleased(Widget::Button* instance) {
	if (instance == _nextPageButton && _gameList->hasNextPage())
		_gameList->nextPage();
	else if (instance == _previousPageButton && _gameList->hasPreviousPage())
		_gameList->previousPage();
	else if (instance == _previousMenu)
		getDelegate()->previous();
	else if (instance == _createGame) {
		getDelegate()->createGame();
		return ;
	} else
		return ;
	_updatePageButtons();
}

void Menu::Join::linePushed(Widget::Table* instance, uint32 line) {
	getDelegate()->joinGame(line);
}

void Menu::Join::_updatePageButtons() {
	_nextPageButton->getElement()->setVisible(isVisible() ? _gameList->hasNextPage() : false);
	_previousPageButton->getElement()->setVisible(isVisible() ? _gameList->hasPreviousPage() : false);
}

void Menu::Join::setVisible(bool visible) {
	Menu::setVisible(visible);
	_serverNameLabel->setVisible(visible);
	_gameList->setVisible(visible);
	_createGame->setVisible(visible);
	_previousMenu->setVisible(visible);
	_updatePageButtons();
}
