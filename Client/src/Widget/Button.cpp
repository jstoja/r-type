//
//  Button.cpp
//  R-Type
//
//  Created by Julien Bordellier on 25/12/12.
//
//
#include "../Graphic/Scene.h"
#include "../Graphic/Sprite.h"
#include "../Graphic/Element.h"
#include "../Graphic/Image.h"
#include "Widget.h"
#include "GraphicWidget.h"
#include "Button.h"
#include "IButtonDelegate.h"

Widget::Button::Button(Graphic::Scene* scene,
                       IButtonDelegate *delegate,
                       std::string const& image) :
GraphicWidget(scene), _delegate(delegate) {
    loadImage(image);
    if (getSprite()) {
        getSprite()->setAutoFrames(3, Graphic::Sprite::Vertical);
        setCurrentFrame(2);
    }
    _eventListener = new Event::Listener(Event::PointerIn
                                         | Event::PointerOut
                                         | Event::PointerPushed
                                         | Event::PointerReleased,
                                         getRect(),
                                         this);
	if (isVisible())
	    Event::Manager::getInstance().addEventListener(_eventListener);
}

Widget::Button::~Button() {
    Event::Manager::getInstance().removeEventListener(_eventListener);
	_eventListener->deleteLater();
}

void    Widget::Button::processEvent(Event::Event const& event) {
  if (event.type == Event::PointerReleased) {
      setCurrentFrame(1);
      _delegate->buttonReleased(this);
  } else if (event.type == Event::PointerPushed) {
      setCurrentFrame(0);
      _delegate->buttonPushed(this);
  } else if (event.type == Event::PointerIn) {
      setCurrentFrame(1);
      _delegate->buttonHovered(this);
  } else if (event.type == Event::PointerOut) {
      setCurrentFrame(2);
      _delegate->buttonUnHovered(this);
  }
}

void            Widget::Button::setPosition(Vec3 const &pos) {
    GraphicWidget::setPosition(pos);
    _eventListener->setRect(getRect());
}

void            Widget::Button::setSize(Vec2 const& size) {
    GraphicWidget::setSize(size);
    _eventListener->setRect(getRect());
}

void			Widget::Button::setVisible(bool visible) {
	if (visible == isVisible())
		return ;
	if (visible)
	    Event::Manager::getInstance().addEventListener(_eventListener);
	else
	    Event::Manager::getInstance().removeEventListener(_eventListener);
	setCurrentFrame(2);
	GraphicWidget::setVisible(visible);
}
