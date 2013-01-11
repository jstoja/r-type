//
//  Button.cpp
//  R-Type
//
//  Created by Julien Bordellier on 25/12/12.
//
//

#include "Widget.h"
#include "Button.h"
#include "IButtonDelegate.h"

Widget::Button::Button(Graphic::Scene* scene,
                       IButtonDelegate *delegate,
                       Widget* parent)
: Widget(scene, parent), _delegate(delegate) {

  addElement();
  _eventListener = new Event::Listener(
        Event::PointerIn
      | Event::PointerOut
      | Event::PointerPushed
      | Event::PointerReleased,
      _element.getRect(),
      this);
}

Widget::Button::Button(Graphic::Scene* scene,
                       IButtonDelegate *delegate,
                       Vec2 const& size,
                       Vec2 const& position,
                       std::string const& image,
                       Widget* parent) :
    Widget(scene, parent), _delegate(delegate) {
    setPosition(position);
    setSize(size);
    loadImage(image);
    _element.getSprite()->setAutoFrames(2, Graphic::Sprite::VERTICAL);
    addElement();
    _eventListener = new Event::Listener(
        Event::PointerIn
      | Event::PointerOut
      | Event::PointerPushed
      | Event::PointerReleased,
      _element.getRect(),
      this);
  Event::Manager::getInstance().addEventListener(_eventListener);
  addElement();

}

Widget::Button::~Button() {
}

void    Widget::Button::setCurrentFrame(uint32 nb) {
    _element.setCurrentFrame(nb);
}

void    Widget::Button::processEvent(Event::Event const& event) {
  if (event.type == Event::PointerReleased) {
    _delegate->buttonClicked(*this);
  }
}
