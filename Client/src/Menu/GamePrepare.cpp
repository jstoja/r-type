//
//  GamePrepare.cpp
//  R-Type
//
//  Created by Gael du Plessix on 16/01/13.
//
//

#include "GamePrepare.h"

Menu::GamePrepare::GamePrepare(Graphic::Scene *scene, IMenuDelegate* delegate,
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
    
	_playerList = new Widget::Table(2, "table-lines.png", scene, this);
	_playerList->setColumnAlignement(Widget::Table::Right, 1);
	std::vector<std::string> names;
	names.push_back("PLAYER");
	names.push_back("STATUS");
	_playerList->setHeaderNames(names);
	float x = scene->getViewport().x / 2, y = scene->getViewport().y - 4.6;
	_playerList->setPosition(Vec3(x, y));

	_readyButton = new Widget::Button(scene, this, "button-ready.png");
	_readyButton->setSize(Vec2(2.8, 0.725));
	_readyButton->setPosition(Vec3(scene->getViewport().x - 2, 1));
}

Menu::GamePrepare::~GamePrepare(void) {
    delete _serverNameLabel;
    delete _previousMenu;
    delete _playerList;
    delete _readyButton;
}

void Menu::GamePrepare::buttonReleased(Widget::Button* instance) {
	if (instance == _previousMenu)
		getDelegate()->previous();
}