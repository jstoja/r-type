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

    loadImage("button.png");
    setPosition(Vec2(1.0, 1.0));
    setSize(Vec2(1.0, 1.0));
    _element.getSprite()->setAutoFrames(3, Graphic::Sprite::VERTICAL);
    _element.setCurrentFrame(0);
    addElement();

   _eventListener = new Event::Listener(
        Event::PointerIn
      | Event::PointerOut
      | Event::PointerPushed
      | Event::PointerReleased,
      _element.getRect(),
      this);

   Event::Manager::getInstance().addEventListener(_eventListener);
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
    _element.getSprite()->setAutoFrames(3, Graphic::Sprite::VERTICAL);
    _element.setCurrentFrame(0);
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
    std::cout << "event fired" << std::endl;
  if (event.type == Event::PointerReleased) {
      _element.setCurrentFrame(2);
    _delegate->buttonReleased(*this);
  } else if (event.type == Event::PointerPushed) {
      _element.setCurrentFrame(1);
      _delegate->buttonPushed(*this);
  } else if (event.type == Event::PointerIn) {
      _element.setCurrentFrame(2);
      _delegate->buttonHovered(*this);
  } else if (event.type == Event::PointerOut) {
      _element.setCurrentFrame(0);
      _delegate->buttonUnHovered(*this);
  }
}

Graphic::Sprite *Widget::Button::getSprite() const {
    return _element.getSprite();
}
