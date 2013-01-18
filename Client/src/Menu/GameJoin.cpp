//
//  Join.cpp
//  R-Type
//
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include <sstream>

#include "GameJoin.h"
#include "Graphic/Scene.h"

Menu::GameJoin::GameJoin(Graphic::Scene *scene, IMenuDelegate* delegate, std::string const& serverName, std::string const& gameName) :
	Menu(scene, delegate) {
	_previousMenu = new Widget::Button(scene, this, "button-left-arrow.png");

	std::string upperName = serverName;
    std::transform(serverName.begin(), serverName.end(), upperName.begin(), ::toupper);
    _serverNameLabel = new Widget::Label(scene, upperName);

	_labelsBackground = new Widget::GraphicWidget(scene, "group-background.png");

	_joiningGameLabel = new Widget::Label(scene, "JOINING GAME:");

	upperName = gameName;
    std::transform(gameName.begin(), gameName.end(), upperName.begin(), ::toupper);
	_gameNameLabel = new Widget::Label(scene, upperName);

	_joiningStateLabel = new Widget::Label(scene, "LOADING RESOURCES...");

	_progressBar = new Widget::ProgressBar(scene, "progress-bar.png");
	_progressBar->setProgress(0);
	_update();
}

Menu::GameJoin::~GameJoin(void) {
	delete _serverNameLabel;
	delete _joiningGameLabel;
	delete _gameNameLabel;
	delete _joiningStateLabel;
	delete _previousMenu;
	delete _progressBar;
	delete _labelsBackground;
}

void Menu::GameJoin::setProgress(float32 progress) {
	_progressBar->setProgress(progress);
}

void Menu::GameJoin::buttonReleased(Widget::Button* instance) {
	if (instance == _previousMenu)
		getDelegate()->previous();
}

void Menu::GameJoin::setVisible(bool visible) {
	Menu::setVisible(visible);
	_serverNameLabel->setVisible(visible);
	_previousMenu->setVisible(visible);
	_joiningGameLabel->setVisible(visible);
	_gameNameLabel->setVisible(visible);
	_joiningStateLabel->setVisible(visible);
	_progressBar->setVisible(visible);
	_labelsBackground->setVisible(visible);
	if (visible)
		_update();
}

void	Menu::GameJoin::_update() {
		_previousMenu->setSize(Vec2(0.56, 0.575));
		_previousMenu->setPosition(Vec3(_previousMenu->getSize().x / 2 + 0.425, getScene()->getViewport().y - 0.8));

	    _serverNameLabel->setPosition(Vec3(getScene()->getViewport().x / 2, getScene()->getViewport().y - 0.8));
		_serverNameLabel->setSize(Vec2(getScene()->getViewport().x - (0.425 * 2), 0.50));
		_serverNameLabel->setTextAligment(Widget::Label::TextAlignRight);

		_labelsBackground->setSize(Vec2(getScene()->getViewport().x - 2 * 0.3, 1.2));
		_labelsBackground->setPosition(Vec3(getScene()->getViewport().x / 2, getScene()->getViewport().y / 2 + _labelsBackground->getSize().y / 2, 0.1));

		_joiningGameLabel->setSize(Vec2(_labelsBackground->getSize().x - 2 * 0.2, 0.38));
		_joiningGameLabel->setPosition(_labelsBackground->getPosition() + Vec3(0, 0, 0.1));
		_joiningGameLabel->setTextAligment(Widget::Label::TextAlignLeft);

		_gameNameLabel->setSize(Vec2(_labelsBackground->getSize().x - 2 * 0.2 - 3.8, 0.36));
		_gameNameLabel->setPosition(Vec3(getScene()->getViewport().x / 2 + 1.8, getScene()->getViewport().y / 2 + _labelsBackground->getSize().y / 2, 0.2));
		_gameNameLabel->setTextAligment(Widget::Label::TextAlignLeft);

		_joiningStateLabel->setSize(Vec2(_labelsBackground->getSize().x - 2 * 0.2, 0.38));
		_joiningStateLabel->setPosition(_labelsBackground->getPosition() + Vec3(0, 0, 0.1));
		_joiningStateLabel->setTextAligment(Widget::Label::TextAlignRight);

		_progressBar->setSize(Vec2(getScene()->getViewport().x - 2 * 0.3, 1.2));
		_progressBar->setPosition(Vec3(getScene()->getViewport().x / 2, getScene()->getViewport().y / 2 - _progressBar->getSize().y / 2, 0.2));
}

void Menu::GameJoin::setServerName(std::string const& serverName) {
	_serverNameLabel->setText(serverName);
}
