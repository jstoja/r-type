//
//  UserInterface.cpp
//  R-Type
//
//  Created by Gael du Plessix on 14/01/13.
//  Copyright (c) 2013 EPITECH. All rights reserved.
//

#include "UserInterface.h"

#include "Graphic/Image.h"
#include <sstream>

const float32 UserInterface::_maxViewportX = 1000000000.0;

UserInterface::UserInterface(IUserInterfaceDelegate* delegate) :
_delegate(delegate), _time(), _sceneries(), _currentMenu(NULL),
_messageLabel(NULL) {
    // Create the sceneries used in all the user interface
    _createSceneries();
    
    // Debug
    //_loginMenu = new Menu::Login(_delegate->getScene(), this);
    _currentMenu = new Menu::NewGame(_delegate->getScene(), this, "The server of the death");
    return ;
    
    // Present welcome menu
    _currentMenu = new Menu::Welcome(_delegate->getScene(), this);
}

UserInterface::~UserInterface(void) {
    if (_currentMenu)
        delete _currentMenu;
}

void UserInterface::update(void) {
    float32 xPos = (float32)_time.getEllapsedTime() / 1000;
    if (xPos > _maxViewportX)
        xPos = 0;
    _delegate->getScene()->setViewportPosition(Vec2(xPos, 0));
}

void UserInterface::presentMessage(std::string const& message) {
    _messageLabel = new Widget::Label(_delegate->getScene());
    _messageLabel->setText(message);
    _messageLabel->setPosition(Vec3(_delegate->getScene()->getViewport().x,
                                    _delegate->getScene()->getViewport().y)
                               /2);
    _messageLabel->setSize(Vec2(_delegate->getScene()->getViewport().x, 0.6));
}

void UserInterface::hideMessage(void) {
    if (_messageLabel)
        delete _messageLabel;
}

void UserInterface::welcomeCompleted(void) {
    delete _currentMenu;
    
    // Present login menu
    _currentMenu = new Menu::Login(_delegate->getScene(), this);
}

void UserInterface::loginCompleted(std::string const& login,
								   std::string const& ipAdress,
								   std::string const& port) {
    std::stringstream str;
    str << "CONNECTION TO " << login << "@" << ipAdress << ":" << port << "...";
    delete _currentMenu;    
    presentMessage(str.str());
}

void UserInterface::newGameCompleted(std::string const& name,
                                     uint32 nbPlayers) {
    std::stringstream str;
    str << "CREATING GAME " << name << " WITH " << nbPlayers << " PLAYERS...";
    delete _currentMenu;    
    presentMessage(str.str());
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
