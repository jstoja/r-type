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
    _serverLabel = new Widget::Label(scene, "SERVER:", Vec3(0x5658a2));
    _serverLabel->setPosition(Vec3(1.8, scene->getViewport().y - 0.8));
    _serverLabel->setSize(Vec2(0.8, 0.50));
    
    std::string upperName = serverName;
    std::transform(serverName.begin(), serverName.end(), upperName.begin(), ::toupper);
    _serverNameLabel = new Widget::Label(scene, upperName);
    _serverNameLabel->setTextAligment(Widget::Label::TextAlignLeft);
    _serverNameLabel->setPosition(Vec3(3.8, scene->getViewport().y - 0.8));
    _serverNameLabel->setSize(Vec2(0.8, 0.50));
    
    _joinGameLabel = new Widget::Label(scene, "JOIN A GAME");
    _joinGameLabel->setPosition(Vec3(scene->getViewport().x/2,
                                    scene->getViewport().y-2));
    _joinGameLabel->setSize(Vec2(scene->getViewport().x, 0.75));

	_gameList = new Widget::Table(2, "table-lines.png", scene, this);
	_gameList->setColumnAlignement(Widget::Table::Right, 1);
	std::vector<std::string> names;
	names.push_back("GAMES");
	names.push_back("SLOTS");
	_gameList->setHeaderNames(names);
	float x = scene->getViewport().x / 2, y = scene->getViewport().y - 5;
	_gameList->setPosition(Vec3(x, y));
	_nextPageButton = new Widget::Button(scene, this, "button-right-arrow.png");
	_nextPageButton->setSize(Vec2(0.56, 0.575));
	_nextPageButton->setPosition(Vec3(x + _gameList->getSize().x / 2 - _nextPageButton->getSize().x / 2, y - _gameList->getSize().y / 2 - _nextPageButton->getSize().y / 2));
	_nextPageButton->getElement()->setVisible(false);
	_previousPageButton = new Widget::Button(scene, this, "button-left-arrow.png");
	_previousPageButton->setSize(Vec2(0.56, 0.575));
	_previousPageButton->setPosition(Vec3(x + _gameList->getSize().x / 2 - _previousPageButton->getSize().x / 2 - _previousPageButton->getSize().x, y - _gameList->getSize().y / 2 - _previousPageButton->getSize().y / 2));
	_previousPageButton->getElement()->setVisible(false);
	_createGame = new Widget::Button(scene, this, "button-new-game.png");
	_createGame->setSize(Vec2(3.45, 0.575));
	_createGame->setPosition(Vec3(x - _gameList->getSize().x / 2 + _createGame->getSize().x / 2, y - _gameList->getSize().y / 2 - _createGame->getSize().y / 2));
}

Menu::Join::~Join(void) {
	delete _serverLabel;
	delete _serverNameLabel;
	delete _joinGameLabel;
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
		_gameList->setColor(idx, Vec3(0.8, 0.8, 0.8));
	_updatePageButtons();
}

void Menu::Join::buttonReleased(Widget::Button* instance) {
	if (instance == _nextPageButton && _gameList->hasNextPage())
		_gameList->nextPage();
	else if (instance == _previousPageButton && _gameList->hasPreviousPage())
		_gameList->previousPage();
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
	_nextPageButton->getElement()->setVisible(_gameList->hasNextPage());
	_previousPageButton->getElement()->setVisible(_gameList->hasPreviousPage());
}

void Menu::Join::setVisible(bool visible) {
	_serverLabel->setVisible(visible);
	_serverNameLabel->setVisible(visible);
	_joinGameLabel->setVisible(visible);
	_gameList->setVisible(visible);
	_nextPageButton->setVisible(visible);
	_previousPageButton->setVisible(visible);
	_createGame->setVisible(visible);
	Menu::setVisible(visible);
}
