//
//  GamePrepare.cpp
//  R-Type
//
//  Created by Gael du Plessix on 16/01/13.
//
//

#include "GamePrepare.h"

#include <sstream>

Menu::GamePrepare::GamePrepare(Graphic::Scene *scene, IMenuDelegate* delegate)
: Menu(scene, delegate) {
    
	_previousMenu = new Widget::Button(scene, this, "button-left-arrow.png");
	_previousMenu->setSize(Vec2(0.56, 0.575));
	_previousMenu->setPosition(Vec3(_previousMenu->getSize().x / 2 + 0.425, scene->getViewport().y - 0.8));
    
    _serverNameLabel = new Widget::Label(scene, "");
    _serverNameLabel->setPosition(Vec3(scene->getViewport().x / 2, scene->getViewport().y - 0.8));
	_serverNameLabel->setSize(Vec2(scene->getViewport().x - (0.425 * 2), 0.50));
    _serverNameLabel->setTextAligment(Widget::Label::TextAlignRight);
    
    _gameLabel = new Widget::Label(scene, "GAME:", Vec3(0x5658a2));
    _gameLabel->setPosition(Vec3(0.9, scene->getViewport().y - 2));
	_gameLabel->setSize(Vec2(1, 0.475));
    _gameLabel->setTextAligment(Widget::Label::TextAlignLeft);
    
    _gameNameLabel = new Widget::Label(scene, "");
    _gameNameLabel->setPosition(Vec3(3.2, scene->getViewport().y - 2));
	_gameNameLabel->setSize(Vec2(1, 0.475));
    _gameNameLabel->setTextAligment(Widget::Label::TextAlignLeft);
    
    _nbPlayersLabel = new Widget::Label(scene, "NB PLAYERS:", Vec3(0x5658a2));
    _nbPlayersLabel->setPosition(Vec3(0.9, scene->getViewport().y - 2.7));
	_nbPlayersLabel->setSize(Vec2(1, 0.475));
    _nbPlayersLabel->setTextAligment(Widget::Label::TextAlignLeft);
    
    _nbPlayersValueLabel = new Widget::Label(scene, "");
    _nbPlayersValueLabel->setPosition(Vec3(5.2, scene->getViewport().y - 2.7));
	_nbPlayersValueLabel->setSize(Vec2(1, 0.475));
    _nbPlayersValueLabel->setTextAligment(Widget::Label::TextAlignLeft);
    
	_playerList = new Widget::Table(2, "table-lines.png", scene, this);
	_playerList->setColumnAlignement(Widget::Table::Right, 1);
	std::vector<std::string> names;
	names.push_back("PLAYER");
	names.push_back("STATUS");
	_playerList->setHeaderNames(names);
	_playerList->setPosition(Vec3(scene->getViewport().x / 2,
                                  scene->getViewport().y / 2 - 0.9));
    _playerList->setLineNumberByPage(4);
    
	_readyButton = new Widget::Button(scene, this, "button-ready.png");
	_readyButton->setSize(Vec2(2.8, 0.725));
	_readyButton->setPosition(Vec3(scene->getViewport().x - 1.85, 0.8));
    
    _waitingLabel = new Widget::Label(scene, "WAITING FOR OTHER PLAYERS...");
    _waitingLabel->setPosition(Vec3(scene->getViewport().x - 1.85, 0.8));
	_waitingLabel->setSize(Vec2(2.8, 0.42));
    _waitingLabel->setTextAligment(Widget::Label::TextAlignRight);
    _waitingLabel->setVisible(false);
}

Menu::GamePrepare::~GamePrepare(void) {
    delete _previousMenu;
    delete _serverNameLabel;
    delete _gameLabel;
    delete _gameNameLabel;
    delete _nbPlayersLabel;
    delete _nbPlayersValueLabel;
    delete _playerList;
    delete _readyButton;
    delete _waitingLabel;
}

void Menu::GamePrepare::buttonReleased(Widget::Button* instance) {
	if (instance == _previousMenu)
		getDelegate()->previous();
    if (instance == _readyButton) {
        _readyButton->setVisible(false);
		getDelegate()->playerReady();
        _waitingLabel->setVisible(true);
    }
}

void Menu::GamePrepare::setCurrentGame(Game* game) {
	setGameName(game->getName());
	_playerList->clearDatas();
	std::list<Player*> const& players = game->getPlayers();
	for (std::list<Player*>::const_iterator it = players.begin(); it != players.end(); ++it)
		_addPlayer((*it)->getName(), (*it)->isReady());
    std::stringstream nbPlayersStr;
	nbPlayersStr << game->getNbPlayer() << " / " << game->getNbSlot();
	_nbPlayersValueLabel->setText(nbPlayersStr.str());
}

void Menu::GamePrepare::_addPlayer(const std::string &name, bool ready) {
    std::vector<std::string>	line;
    line.reserve(2);
	line.push_back(name);
    line.push_back(ready ? "READY" : "NOT READY");
	uint32 idx = _playerList->addLine(line);
	if (ready)
		_playerList->setColor(idx, 1, Vec3(0x56a26f));
    else
		_playerList->setColor(idx, 1, Vec3(0xff7b7b));
}

void Menu::GamePrepare::setVisible(bool visible) {
    _previousMenu->setVisible(visible);
    _serverNameLabel->setVisible(visible);
    _gameLabel->setVisible(visible);
    _gameNameLabel->setVisible(visible);
    _nbPlayersLabel->setVisible(visible);
    _nbPlayersValueLabel->setVisible(visible);
    _playerList->setVisible(visible);
    _readyButton->setVisible(visible);
    _waitingLabel->setVisible(false);
}

void Menu::GamePrepare::setServerName(std::string const& serverName) {
	_serverNameLabel->setText(serverName);
}

void Menu::GamePrepare::setGameName(std::string const& gameName) {
	_gameNameLabel->setText(gameName);
}