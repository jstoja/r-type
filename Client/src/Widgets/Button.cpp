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
                       Widget* parent)
: GraphicWidget(scene, parent), _delegate(delegate) {

    loadImage("./button.png");
    GraphicWidget::setPosition(Vec3(1.0, 1.0));
    GraphicWidget::setSize(Vec2(1.0, 1.0));
    if (getSprite() != NULL) {
        getSprite()->setAutoFrames(3, Graphic::Sprite::VERTICAL);
        setCurrentFrame(0);
    }
    _eventListener = new Event::Listener(
        Event::PointerIn
      | Event::PointerOut
      | Event::PointerPushed
      | Event::PointerReleased,
        getRect(),
      this);
   Event::Manager::getInstance().addEventListener(_eventListener);
   addElement();
}

Widget::Button::Button(Graphic::Scene* scene,
                       IButtonDelegate *delegate,
                       Vec2 const& size,
                       Vec3 const& position,
                       std::string const& image,
                       Widget* parent) :
    GraphicWidget(scene, parent), _delegate(delegate) {
    loadImage(image);
    GraphicWidget::setPosition(position);
    GraphicWidget::setSize(size);
    if (getSprite()) {
        getSprite()->setAutoFrames(3, Graphic::Sprite::VERTICAL);
        setCurrentFrame(0);
    }
    _eventListener = new Event::Listener(
        Event::PointerIn
      | Event::PointerOut
      | Event::PointerPushed
      | Event::PointerReleased,
      getRect(),
      this);
  Event::Manager::getInstance().addEventListener(_eventListener);
  addElement();
}

Widget::Button::~Button() {
}

void    Widget::Button::processEvent(Event::Event const& event) {
    std::cout << "event fired" << std::endl;
  if (event.type == Event::PointerReleased) {
      setCurrentFrame(2);
      _delegate->buttonReleased(*this);
  } else if (event.type == Event::PointerPushed) {
      setCurrentFrame(1);
      _delegate->buttonPushed(*this);
  } else if (event.type == Event::PointerIn) {
      setCurrentFrame(2);
      _delegate->buttonHovered(*this);
  } else if (event.type == Event::PointerOut) {
      setCurrentFrame(0);
      _delegate->buttonUnHovered(*this);
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
