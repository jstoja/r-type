//
//  NewGame.cpp
//  R-Type
//
//  Created by Gael du Plessix on 15/01/13.
//
//

#include "NewGame.h"

#include <algorithm>

Menu::NewGame::NewGame(Graphic::Scene *scene, IMenuDelegate* delegate,
                       std::string const& serverName)
: Menu(scene, delegate), _nbPlayers(1) {
    
    std::string upperName = serverName;
    std::transform(serverName.begin(), serverName.end(), upperName.begin(), ::toupper);
    _serverNameLabel = new Widget::Label(scene, upperName);
    _serverNameLabel->setPosition(Vec3(scene->getViewport().x / 2, scene->getViewport().y - 0.8));
	_serverNameLabel->setSize(Vec2(scene->getViewport().x - (0.425 * 2), 0.50));
    _serverNameLabel->setTextAligment(Widget::Label::TextAlignRight);

	_previousMenu = new Widget::Button(scene, this, "button-left-arrow.png");
	_previousMenu->setSize(Vec2(0.56, 0.575));
	_previousMenu->setPosition(Vec3(_previousMenu->getSize().x / 2 + 0.425, scene->getViewport().y - 0.8));

    _newGameLabel = new Widget::Label(scene, "NEW GAME");
    _newGameLabel->setPosition(Vec3(scene->getViewport().x/2,
                                    scene->getViewport().y-3));
    _newGameLabel->setSize(Vec2(scene->getViewport().x, 0.75));
    
    _nameLabel = new Widget::Label(scene, "GAME NAME");
    _nameLabel->setTextAligment(Widget::Label::TextAlignRight);
    _nameLabel->setSize(Vec2(4.8, 0.525));
    _nameLabel->setPosition(Vec3(scene->getViewport().x/2 - 3.2,
                               4.2, 0));
    
    _nameField = new Widget::TextEdit(scene, this, "text-field.png");
    _nameField->setValue("");
    _nameField->setSize(Vec2(6.5, 1.25));
    _nameField->setPosition(Vec3(scene->getViewport().x/2 + 2.6,
                                 4.2, 0));

    _playersLabel = new Widget::Label(scene, "PLAYERS");
    _playersLabel->setTextAligment(Widget::Label::TextAlignRight);
    _playersLabel->setSize(Vec2(4.8, 0.525));
    _playersLabel->setPosition(Vec3(scene->getViewport().x/2 - 3.2,
                                    3, 0));
    
    // Create the selector of players number
    Graphic::Image image;
    image.loadFromResource("number-field.png");
    for (int i = 0; i < 4; ++i) {
        Widget::GraphicWidget* button = new Widget::GraphicWidget(scene);
        Graphic::Texture* texture = new Graphic::Texture();
        texture->setData(image.getWidth(), image.getHeight(), image.getPixelsPtr());
        Graphic::Sprite* sprite = new Graphic::Sprite();
        sprite->setTexture(texture);
        // Create button frames
        sprite->addFrame(Graphic::Sprite::Frame(Vec2((float32)i/4,
                                                     0),
                                                Vec2((float32)(i + 1)/4,
                                                     0.5)));
        sprite->addFrame(Graphic::Sprite::Frame(Vec2((float32)i/4,
                                                     0.5),
                                                Vec2((float32)(i + 1)/4,
                                                     1)));
        button->setSprite(sprite);
        button->setCurrentFrame((i + 1) == _nbPlayers ? 0 : 1);
        button->setSize(Vec2(1.4, 1.4));
        button->setPosition(Vec3(scene->getViewport().x/2
                                 + 0.04 + i * 1.4,
                                 3, 0));
        _playersSelect.push_back(button);
    }
    
    // Add an event listener in order to select the number of players
    _eventListener = new Event::Listener(Event::PointerPushed, this);
    Event::Manager::getInstance().addEventListener(_eventListener);
    
    _newGameButton = new Widget::Button(scene, this, "button-new-game.png");
    _newGameButton->setSize(Vec2(4.96, 0.85));
    _newGameButton->setPosition(Vec3(scene->getViewport().x/2, 1));
}

Menu::NewGame::~NewGame(void) {
    delete _serverNameLabel;
    delete _newGameLabel;
    delete _nameLabel;
    delete _nameField;
    delete _playersLabel;
    for (int i = 0; i < _playersSelect.size(); ++i) {
        delete _playersSelect[i];
    }
    delete _newGameButton;
    
    Event::Manager::getInstance().removeEventListener(_eventListener);
    _eventListener->deleteLater();
}

void Menu::NewGame::processEvent(Event::Event const& event) {
    for (int i = 0; i < _playersSelect.size(); ++i) {
        _playersSelect[i]->getElement()->setCurrentFrame(1);
        if (_playersSelect[i]->getElement()->getRect().in(event.pos)) {
            _nbPlayers = i + 1;
        }
    }
    _playersSelect[_nbPlayers - 1]->getElement()->setCurrentFrame(0);
}

void Menu::NewGame::buttonReleased(Widget::Button* instance) {
    if (instance == _newGameButton && _nameField->getValue() != "")
        getDelegate()->newGameCompleted(_nameField->getValue(), _nbPlayers);
	else if (instance == _previousMenu)
		getDelegate()->previous();
}

void Menu::NewGame::setVisible(bool visible) {
    _serverNameLabel->setVisible(visible);
    _newGameLabel->setVisible(visible);
    _newGameButton->setVisible(visible);
    _nameLabel->setVisible(visible);
    _nameField->setVisible(visible);
	_playersLabel->setVisible(visible);
	_previousMenu->setVisible(visible);
	for (unsigned int i = 0; i < _playersSelect.size(); ++i)
		_playersSelect[i]->setVisible(visible);
	Menu::setVisible(visible);
}
